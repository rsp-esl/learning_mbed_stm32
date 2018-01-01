#include "BH1750.h"

BH1750::BH1750( PinName sda, PinName scl, uint8_t addr, uint32_t freq ) 
  : _sda(sda), _scl(scl), _addr(addr << 1), 
    _mode( BH1750_ONE_TIME_HIGH_RES_MODE ), _status(0)
{
   _i2c = new I2C( sda, scl );
   frequency( freq );
}

BH1750::~BH1750() {
   delete _i2c;
}

bool BH1750::begin( uint8_t measure_mode ) {
   _mode = measure_mode;
   reset();
   mode( _mode );
   return !is_error();
}

void BH1750::frequency( uint32_t freq_hz ) {
   _i2c->frequency( freq_hz );
}

bool BH1750::mode( uint8_t measure_mode ) {
   switch (measure_mode) {
      case BH1750_CONT_HIGH_RES_MODE:
      case BH1750_CONT_HIGH_RES_MODE_2:
      case BH1750_CONT_LOW_RES_MODE:
      case BH1750_ONE_TIME_HIGH_RES_MODE:
      case BH1750_ONE_TIME_HIGH_RES_MODE_2:
      case BH1750_ONE_TIME_LOW_RES_MODE:
           _mode = measure_mode;
           write_reg( _mode );
           break;
      default:
           return false;
   }
   return !is_error();
}

bool BH1750::read( float & intensity ) {
   uint16_t result;
   
   switch (_mode) {
      case BH1750_ONE_TIME_HIGH_RES_MODE:
      case BH1750_ONE_TIME_HIGH_RES_MODE_2:
      case BH1750_ONE_TIME_LOW_RES_MODE:
         if ( !write_reg( _mode ) ) {
            return false;
         }
         wait_ms(150);
         break;
      default: break;
    }

   if ( !read_raw( result ) ) {
      return false;      
   }
   intensity = result;
   intensity /= 1.2f;
   return true;
}

void BH1750::reset() {
   write_reg( BH1750_RESET );
   wait_ms(20);
}

void BH1750::power_on() {
   write_reg( BH1750_POWER_ON );
   wait_ms(10);
}

void BH1750::power_down() {
    write_reg( BH1750_POWER_DOWN );
}

bool BH1750::write_reg( uint8_t data ) {
   _buf[0] = data;
   _status = _i2c->write( _addr, (const char *)_buf, 1, false );
   return !is_error();
}

bool BH1750::read_reg( uint8_t &data ) {
   _status = _i2c->read( _addr, (char *)_buf, 1, false );
   data = _buf[0];
   return !is_error();
}

bool BH1750::read_raw( uint16_t &data ) {
    _status = _i2c->read( _addr, (char *)_buf, 2, false );
    if ( is_error() ) { // no ACK
        return false;
    }
    data = _buf[0];
    data = (data << 8) | _buf[1];
    return true;
}

/////////////////////////////////////////////////////////////////////////

