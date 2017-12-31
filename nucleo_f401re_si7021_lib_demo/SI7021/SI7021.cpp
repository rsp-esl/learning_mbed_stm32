///////////////////////////////////////////////////////////////////////////////
#include "SI7021.h"
#include "mbed.h"

SI7021::SI7021( PinName sda, PinName scl, int addr, int freq ) 
   : _sda(sda), _scl(scl), _freq(freq)
{
   _addr = (addr << 1);
   _i2c  = new I2C( _sda, _scl );
   _i2c->frequency( _freq );
}

SI7021::~SI7021() {
   delete _i2c;
}

bool SI7021::begin() {
  int ack;
  _buf[0] = SI7021_RESET_CMD;
  ack = _i2c->write( _addr, (const char *) _buf, 1 ); 
  if ( ack != 0 ) { // no ACK
    return false;
  }
  wait_ms(25);
  return true;    
}

void SI7021::frequency( int freq ) {
  _freq = freq;
  _i2c->frequency( _freq );
}


bool SI7021::read( float &temperature, float &humidity ) {
  int ack;

  /// read temperature  
  _buf[0] = SI7021_MEASTEMP_NOHOLD_CMD;
  ack = _i2c->write( _addr, (const char *)_buf, 1 ); 
  if ( ack != 0 ) { // no ACK
    return false;
  }
  wait_ms(25);
  ack = _i2c->read( _addr, (char *)_buf, 3 );
  if ( ack != 0 ) { // no ACK
    return false;
  }
  // note: _buf[2] is the checksum byte 
  if ( crc8(_buf, 2) != _buf[2] ) { // CRC error
    return false;
  }  

  uint16_t temp = _buf[0];
  temp = (temp << 8) | _buf[1];

  temperature = temp;
  temperature *= 175.72f;
  temperature /= 65536;
  temperature -= 46.85f;
    
  /// read humidity 
  _buf[0] = SI7021_MEASRH_NOHOLD_CMD;
  ack = _i2c->write( _addr, (const char *)_buf, 1 ); 
  if ( ack != 0 ) { // no ACK
    return false;
  }
  wait_ms(25);
  ack = _i2c->read( _addr, (char *)_buf, 3 );
  if ( ack != 0 ) { // no ACK
    return false;
  }
  // note: _buf[2] is the checksum byte 
  if ( crc8(_buf, 2) != _buf[2] ) { // CRC error
    return false;
  }  

  uint16_t humid = _buf[0];
  humid = (humid << 8) | _buf[1];
 
  humidity = humid;
  humidity *= 125;
  humidity /= 65536;
  humidity -= 6;

  return true;      
}

uint8_t SI7021::crc8( uint8_t data[], int len ) {
  uint8_t crc = 0x00;
  for ( int i=0; i < len; ++i) {
    crc ^= data[i];
    for (int j=8; j > 0; --j) {
      if (crc & 0x80) {
        crc = (crc << 1) ^ 0x131;
      } else {
        crc = crc << 1;
      }
    }
  }
  return crc;
}
///////////////////////////////////////////////////////////////////////////////
