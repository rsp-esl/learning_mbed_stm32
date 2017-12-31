/////////////////////////////////////////////////////////////////////////
#include "BH1750.h"
#include "mbed.h"

BH1750::BH1750( I2C *i2c, uint8_t addr ) {
   _i2c  = i2c;
   _addr = (addr << 1);
}

bool BH1750::init( ) {
   int ack;
   uint8_t buf[2];
   buf[0] = BH1750_CONT_HIGH_RES_MODE;
   ack = _i2c->write( _addr, (const char *)buf, 1 );
   wait_ms(10);
   if ( ack != 0 ) { // no ACK
      return false;
   }
   return true;
}

int BH1750::read() {
   int ack;
   uint8_t buf[2];
   ack = _i2c->read( _addr, (char *)buf, 2 );
   if ( ack != 0 ) {
     return -1;
   }
   uint32_t level = buf[0];
   level = (level << 8) | buf[1];
   return (10*level)/12; // Convert raw value to lux
}
/////////////////////////////////////////////////////////////////////////
