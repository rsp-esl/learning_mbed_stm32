/////////////////////////////////////////////////////////////////////////
#include "BME280.h"

/////////////////////////////////////////////////////////////////////////
// Written by Rawat S. (KMUTNB, Bangkok/Thailand)
// based on the Adafruit's BME280 library
//  => https://github.com/adafruit/Adafruit_BME280_Library
/////////////////////////////////////////////////////////////////////////

BME280::BME280( PinName sda, PinName scl, uint8_t addr, uint32_t freq ) 
  : _sda(sda), _scl(scl), _addr(addr << 1), _status(0)
{
   _i2c = new I2C( sda, scl );
   frequency( freq );
}

BME280::~BME280() {
   delete _i2c;
}

bool BME280::begin() {
   _status = 0;
   if ( read_chip_id() != 0x60 ) {
     return false;
   }
   read_coefficients();
   write8( BME280_REGISTER_CONTROLHUMID, 0x05 ); // 16x oversampling 
   write8( BME280_REGISTER_CONTROL, 0xB7 );      // 16x ovesampling, normal mode
   wait_ms(5);
   read_temperature();
   
   bool ok = !is_error();
   _status = 0;
   return ok;
}

void BME280::frequency( uint32_t freq_hz ) {
   _i2c->frequency( freq_hz );
}

uint8_t BME280::read_chip_id( void ) {
   return read8( BME280_REGISTER_CHIPID );
}

bool BME280::read( float & temperature, float & humidity, float & pressure ) {
   temperature = read_temperature();
   humidity    = read_humidity();
   pressure    = read_pressure();
   
   bool ok = !is_error();
   _status = 0;
   return ok;
}   

//  Writes an 8-bit value over I2C
void BME280::write8( uint8_t reg, uint8_t value ) {
  _buf[0] = reg;
  _buf[1] = value;
  _status |= _i2c->write( _addr, (const char *)_buf, 2, false ); 
}

// Reads an 8-bit value over I2C
uint8_t BME280::read8( uint8_t reg ) {
  _buf[0] = reg;
  _status |= _i2c->write( _addr, (const char *)_buf, 1, false ); 
  _status |= _i2c->read( _addr, (char *)_buf, 1, false ); 
  return _buf[0];
}

// Reads a 16-bit value over I2C
uint16_t BME280::read16( uint8_t reg ) {
  _buf[0] = reg;
  _status |= _i2c->write( _addr, (const char *)_buf, 1, false ); 
  wait_us(10);
  _status |= _i2c->read( _addr, (char *)_buf, 2, false ); 
  uint16_t value = _buf[0];
  value = (value << 8) | _buf[1];
  return value;
}

uint16_t BME280::read16_LE( uint8_t reg ) {
  uint16_t temp = read16( reg );
  return (temp >> 8) | (temp << 8); // swap
}

int16_t BME280::readS16( uint8_t reg ) {
  return (int16_t)read16( reg );
}

int16_t BME280::readS16_LE( uint8_t reg ) {
  return (int16_t)read16_LE( reg );
}

// Reads a 24-bit value over I2C
uint32_t BME280::read24( uint8_t reg ) {
  _buf[0] = reg;
  _status |= _i2c->write( _addr, (const char *)_buf, 1, false ); 
  _status |= _i2c->read( _addr, (char *)_buf, 3, false ); 

  uint32_t value;
  value = _buf[0];    
  value = (value << 8) | _buf[1];    
  value = (value << 8) | _buf[2];    
  return value;
}

void BME280::read_coefficients(void) {
    _bme280_calib.dig_T1 = read16_LE(BME280_REGISTER_DIG_T1);
    _bme280_calib.dig_T2 = readS16_LE(BME280_REGISTER_DIG_T2);
    _bme280_calib.dig_T3 = readS16_LE(BME280_REGISTER_DIG_T3);

    _bme280_calib.dig_P1 = read16_LE(BME280_REGISTER_DIG_P1);
    _bme280_calib.dig_P2 = readS16_LE(BME280_REGISTER_DIG_P2);
    _bme280_calib.dig_P3 = readS16_LE(BME280_REGISTER_DIG_P3);
    _bme280_calib.dig_P4 = readS16_LE(BME280_REGISTER_DIG_P4);
    _bme280_calib.dig_P5 = readS16_LE(BME280_REGISTER_DIG_P5);
    _bme280_calib.dig_P6 = readS16_LE(BME280_REGISTER_DIG_P6);
    _bme280_calib.dig_P7 = readS16_LE(BME280_REGISTER_DIG_P7);
    _bme280_calib.dig_P8 = readS16_LE(BME280_REGISTER_DIG_P8);
    _bme280_calib.dig_P9 = readS16_LE(BME280_REGISTER_DIG_P9);

    _bme280_calib.dig_H1 = read8(BME280_REGISTER_DIG_H1);
    _bme280_calib.dig_H2 = readS16_LE(BME280_REGISTER_DIG_H2);
    _bme280_calib.dig_H3 = read8(BME280_REGISTER_DIG_H3);
    _bme280_calib.dig_H4 = (read8(BME280_REGISTER_DIG_H4) << 4) 
                         | (read8(BME280_REGISTER_DIG_H4+1) & 0xF);
    _bme280_calib.dig_H5 = (read8(BME280_REGISTER_DIG_H5+1) << 4)
                         | (read8(BME280_REGISTER_DIG_H5) >> 4);
    _bme280_calib.dig_H6 = (int8_t)read8(BME280_REGISTER_DIG_H6);
}

float BME280::read_temperature(void) {
  int32_t var1, var2;
  int32_t adc_T = read24( BME280_REGISTER_TEMPDATA );

  adc_T >>= 4;
  var1  = ((((adc_T>>3) - ((int32_t)_bme280_calib.dig_T1 <<1))) *
          ((int32_t)_bme280_calib.dig_T2)) >> 11;

  var2  = (((((adc_T>>4) - ((int32_t)_bme280_calib.dig_T1)) *
            ((adc_T>>4) - ((int32_t)_bme280_calib.dig_T1))) >> 12) *
          ((int32_t)_bme280_calib.dig_T3)) >> 14;

  _t_fine = var1 + var2;
  float T = (_t_fine * 5 + 128) >> 8;
  return (T / 100.0f);
}

float BME280::read_humidity(void) {
  int32_t adc_H = read16( BME280_REGISTER_HUMIDDATA );
  int32_t v_x1_u32r;

  v_x1_u32r = (_t_fine - ((int32_t)76800));
  
  v_x1_u32r = (((((adc_H << 14) - (((int32_t)_bme280_calib.dig_H4) << 20) -
          (((int32_t)_bme280_calib.dig_H5) * v_x1_u32r)) + ((int32_t)16384)) >> 15) *
           (((((((v_x1_u32r * ((int32_t)_bme280_calib.dig_H6)) >> 10) *
            (((v_x1_u32r * ((int32_t)_bme280_calib.dig_H3)) >> 11) + ((int32_t)32768))) >> 10) +
          ((int32_t)2097152)) * ((int32_t)_bme280_calib.dig_H2) + 8192) >> 14));

  v_x1_u32r = (v_x1_u32r - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) *
                 ((int32_t)_bme280_calib.dig_H1)) >> 4));
                 
  v_x1_u32r = (v_x1_u32r < 0) ? 0 : v_x1_u32r;
  
  v_x1_u32r = (v_x1_u32r > 419430400) ? 419430400 : v_x1_u32r;
  
  float H = (v_x1_u32r>>12);
  return  (H / 1024.0f);
}

float BME280::read_pressure(void) {
  int64_t var1, var2, p;

  int32_t adc_P = read24(BME280_REGISTER_PRESSUREDATA);
  adc_P >>= 4;

  var1 = ((int64_t)_t_fine) - 128000;
  var2 = var1 * var1 * (int64_t)_bme280_calib.dig_P6;
  var2 = var2 + ((var1*(int64_t)_bme280_calib.dig_P5)<<17);
  var2 = var2 + (((int64_t)_bme280_calib.dig_P4)<<35);
  var1 = ((var1 * var1 * (int64_t)_bme280_calib.dig_P3)>>8) +
         ((var1 * (int64_t)_bme280_calib.dig_P2)<<12);
  var1 = (((((int64_t)1)<<47)+var1))*((int64_t)_bme280_calib.dig_P1)>>33;

  if (var1 == 0) {
    return 0;  // avoid exception caused by division by zero
  }
  p = 1048576 - adc_P;
  p = (((p<<31) - var2)*3125) / var1;
  var1 = (((int64_t)_bme280_calib.dig_P9) * (p>>13) * (p>>13)) >> 25;
  var2 = (((int64_t)_bme280_calib.dig_P8) * p) >> 19;

  float P = ((p + var1 + var2) >> 8) + (((int64_t)_bme280_calib.dig_P7)<<4);
  return (P/256.0f);
}

/////////////////////////////////////////////////////////////////////////

