#ifndef __SHT3x_H
#define __SHT3x_H

#include "mbed.h"

#define SHT3x_I2C_ADDR         (0x44)  // SHT3x-DIS (I2C)

#define SHT3x_SOFT_RESET       (0x30A2)
// single shot mode, no clock stretching
#define SHT3x_ACCURACY_HIGH    (0x2C06)
#define SHT3x_ACCURACY_MEDIUM  (0x2C0D)
#define SHT3x_ACCURACY_LOW     (0x2C10)

class SHT3x {
    public:
      SHT3x( PinName sda, PinName scl, 
             int addr=SHT3x_I2C_ADDR, int freq=100000 );
      ~SHT3x(); 
      bool begin();
      bool read( float &temperature, float &humidity );
      void frequency( int freq );

    private:
      PinName _sda, _scl;
      int _addr;
      int _freq;
      uint8_t _buf[6];
      I2C *_i2c;
      uint8_t crc8( const uint8_t *data, int len );
            
}; // end class

#endif // __SHT3x_H
///////////////////////////////////////////////////////////////////////////////
