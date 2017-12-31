#include "SHT3x.h"
#include "mbed.h"

SHT3x::SHT3x( PinName sda, PinName scl, int addr, int freq ) 
   : _sda(sda), _scl(scl), _freq(freq)
{
   _addr = (addr << 1);
   _i2c  = new I2C( _sda, _scl );
   _i2c->frequency( _freq );
}

SHT3x::~SHT3x() {
   delete _i2c;
}

bool SHT3x::begin() {
  int ack;
  _buf[0] = (SHT3x_SOFT_RESET >> 8) & 0xff;
  _buf[1] = SHT3x_SOFT_RESET & 0xff;
  ack = _i2c->write( _addr, (const char *)_buf, 2 ); 
  if ( ack != 0 ) { // no ACK
    return false;
  }
  wait_ms(10);

  _buf[0] = (SHT3x_ACCURACY_HIGH >> 8) & 0xff;
  _buf[1] = SHT3x_ACCURACY_HIGH & 0xff;
  ack = _i2c->write( _addr, (const char *)_buf, 2 ); 
  if ( ack != 0 ) { // no ACK
    return false;
  }
  return true;    
}

void SHT3x::frequency( int freq ) {
  _freq = freq;
  _i2c->frequency( _freq );
}


bool SHT3x::read( float &temperature, float &humidity ) {
  int ack;
  // Send measurement command
  _buf[0] = (SHT3x_ACCURACY_HIGH >> 8) & 0xff;
  _buf[1] = SHT3x_ACCURACY_HIGH & 0xff; 
  ack = _i2c->write( _addr, (const char *)_buf, 2 ); 
  if ( ack != 0 ) { // no ACK
    return false;
  }
  wait_ms(50); // note: measurement time is about 15 msec

  ack = _i2c->read( _addr, (char *)_buf, 6 );
  if ( ack != 0 ) { // no ACK
    return false;
  }

  // check CRC for both values
  if ( crc8(_buf,2)==_buf[2] && crc8(_buf+3,2)==_buf[5] ) {
    uint16_t value;
    value = (_buf[0] << 8) + _buf[1];
    temperature = ((value * 175.0) / 65535) - 45; // temperature in Celsius.
    value = (_buf[3] << 8) + _buf[4];
    humidity = ((value * 100.0) / 65535); // relative humidity
    return true;
  } 
  return false;      
}

// CRC-8, Polynomial: 0x31  x^8 + x^5 + x^4 + 1, Initial value = 0xff
uint8_t SHT3x::crc8( const uint8_t *data, int len ) {
  uint8_t crc = 0xFF;
  for ( int i=0; i < len; i++ ) {
    crc ^= data[i];
    for ( int j=0; j < 8; j++ ) {
      crc = crc & 0x80 ? (crc << 1) ^ 0x31 : crc << 1;
    }
  }
  return crc;
}
