/////////////////////////////////////////////////////////////////////////
#ifndef __BME280_H
#define __BME280_H

#include "mbed.h"

/////////////////////////////////////////////////////////////////////////
// Written by Rawat S. (KMUTNB, Bangkok/Thailand)
// based on the Adafruit's BME280 library
//  => https://github.com/adafruit/Adafruit_BME280_Library
/////////////////////////////////////////////////////////////////////////

#define BME280_I2C_ADDR          0x76

#define BME280_REGISTER_DIG_T1   0x88
#define BME280_REGISTER_DIG_T2   0x8A
#define BME280_REGISTER_DIG_T3   0x8C
#define BME280_REGISTER_DIG_P1   0x8E
#define BME280_REGISTER_DIG_P2   0x90
#define BME280_REGISTER_DIG_P3   0x92
#define BME280_REGISTER_DIG_P4   0x94
#define BME280_REGISTER_DIG_P5   0x96
#define BME280_REGISTER_DIG_P6   0x98
#define BME280_REGISTER_DIG_P7   0x9A
#define BME280_REGISTER_DIG_P8   0x9C
#define BME280_REGISTER_DIG_P9   0x9E

#define BME280_REGISTER_DIG_H1   0xA1
#define BME280_REGISTER_DIG_H2   0xE1
#define BME280_REGISTER_DIG_H3   0xE3
#define BME280_REGISTER_DIG_H4   0xE4
#define BME280_REGISTER_DIG_H5   0xE5
#define BME280_REGISTER_DIG_H6   0xE7

#define BME280_REGISTER_CHIPID       0xD0
#define BME280_REGISTER_VERSION      0xD1
#define BME280_REGISTER_SOFTRESET    0xE0
#define BME280_REGISTER_CAL26        0xE1 // R calibration stored in 0xE1-0xF0
#define BME280_REGISTER_CONTROLHUMID 0xF2
#define BME280_REGISTER_CONTROL      0xF4
#define BME280_REGISTER_CONFIG       0xF5
#define BME280_REGISTER_PRESSUREDATA 0xF7
#define BME280_REGISTER_TEMPDATA     0xFA
#define BME280_REGISTER_HUMIDDATA    0xFD

typedef struct {
      uint16_t dig_T1;
      int16_t  dig_T2;
      int16_t  dig_T3;

      uint16_t dig_P1;
      int16_t  dig_P2;
      int16_t  dig_P3;
      int16_t  dig_P4;
      int16_t  dig_P5;
      int16_t  dig_P6;
      int16_t  dig_P7;
      int16_t  dig_P8;
      int16_t  dig_P9;

      uint8_t  dig_H1;
      int16_t  dig_H2;
      uint8_t  dig_H3;
      int16_t  dig_H4;
      int16_t  dig_H5;
      int8_t   dig_H6;
      
} bme280_calib_data;
      
/////////////////////////////////////////////////////////////////////////

class BME280 {
public:
    BME280( PinName sda, PinName scl, 
            uint8_t addr=BME280_I2C_ADDR, uint32_t freq_hz=100000 );
    ~BME280();
    bool begin( );
    void frequency( uint32_t freq_hz );
    uint8_t read_chip_id( void );
    bool read( float & temperature, float & humidity, float & pressure );
    inline bool is_error() { return (_status != 0); }

private:
    I2C *     _i2c;
    PinName   _sda, _scl;
    uint8_t   _addr;
    uint8_t   _buf[3];
    int       _status; 
    int32_t   _t_fine;
    bme280_calib_data _bme280_calib;
    
    void      write8(uint8_t reg, uint8_t value);
    uint8_t   read8(uint8_t reg);
    uint16_t  read16(uint8_t reg);
    uint32_t  read24(uint8_t reg);
    int16_t   readS16(uint8_t reg);
    uint16_t  read16_LE(uint8_t reg);  
    int16_t   readS16_LE(uint8_t reg); 
    void      read_coefficients(void);
    float     read_temperature();
    float     read_humidity();
    float     read_pressure();
};

#endif // __BME280_H

/////////////////////////////////////////////////////////////////////////

