#include "DHT2x.h"
#include "mbed.h"

DHT2x::DHT2x( PinName pin ) : _pin(pin), _error(0) {
   _dio = new DigitalInOut( _pin );
   data_output();
   data_high();
}

DHT2x::~DHT2x() {
   delete _dio;
}

bool DHT2x::read_byte( uint8_t &value ){
   uint8_t result = 0x00;
   uint16_t cnt;
   _error = 0; 
   for( int i=0; i < 8; i++ ) {
     cnt = 0;
     while( is_data_low() ) { // wait until DATA goes HIGH.
       if ( ++cnt > 1000 ) { 
         _error = 0x01;  // DATA is stuck LOW.
         return false; 
       }
     }
     wait_us(30); // wait for 30 usec
     result <<= 1;
     if ( is_data_high() ) { // if DATA is HIGH, this bit is 1.
       result |= 1;
     }
     cnt = 0;
     while( is_data_high() ) {  // wait until DATA goes LOW.
       if ( ++cnt > 1000 ) { 
         _error = 0x02; // DATA is stuck HIGH.
         return false; 
       }
     }
   }
   value = result;
   return true;
}

bool DHT2x::read( float &temperature, float &humidity ) {
   _error = 0; // clear error
   // DATA must be configured as output.
   data_output();
   // send start signal
   data_low();
   wait_us(1000);
   data_high();
  // release the bus and wait for the response signal
   data_input();
   wait_us(30);
   if ( is_data_high() ){ // LOW expected
      _error |= 0x02;  // DATA is stuck HIGH.
   }
   wait_us(80);
   if ( is_data_low() ){ // HIGH expected
      _error |= 0x01;  // DATA is stuck lOW.
   }
   wait_us(80);
   if ( _error ) {
     data_output();
     data_high();
     return false;
   }

   // Now the DATA line must be LOW.

   uint8_t value, checksum = 0x00;
   for ( int i=0; i < 5; i++ ) { // read 5 bytes into the buffer
     if ( !read_byte( value ) ) {
        _error |= 0x04;
        break;
     }
     _buf[i] = value;
     if ( i < 4 ) {
        checksum += value;
     }
  }
  data_output();
  data_high();

  if ( _buf[4] != checksum ) {
     _error |= 0x08; // checksum error
     return false;
  }
  
  uint16_t temp = (_buf[2] << 8) + _buf[3]; // temperature in Celsius (0.1 step)
  if (temp & 0x8000) {
    temp &= 0x7fff;
    temp = -temp;
  }
  uint16_t humid = (_buf[0] << 8) + _buf[1]; // rel. humidity in percent (0.1 step)
  
  temperature = temp * 0.1;
  humidity    = humid * 0.1;
  return (_error==0);
}
