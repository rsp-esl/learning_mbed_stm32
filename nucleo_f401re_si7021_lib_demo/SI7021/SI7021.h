///////////////////////////////////////////////////////////////////////////////
#ifndef __SI7021_H
#define __SI7021_H

#include "mbed.h"

#define SI7021_I2C_ADDR         (0x40) 

#define SI7021_MEASRH_HOLD_CMD           0xE5
#define SI7021_MEASRH_NOHOLD_CMD         0xF5
#define SI7021_MEASTEMP_HOLD_CMD         0xE3
#define SI7021_MEASTEMP_NOHOLD_CMD       0xF3
#define SI7021_READPREVTEMP_CMD          0xE0
#define SI7021_RESET_CMD                 0xFE
#define SI7021_WRITERHT_REG_CMD          0xE6
#define SI7021_READRHT_REG_CMD           0xE7
#define SI7021_WRITEHEATER_REG_CMD       0x51
#define SI7021_READHEATER_REG_CMD        0x11
#define SI7021_ID1_CMD                   0xFA0F
#define SI7021_ID2_CMD                   0xFCC9
#define SI7021_FIRMVERS_CMD              0x84B8

/*
 Si7021
  - 12-bit RH Resolution 0.025
  - +/-3% RH Accuracy
  - 14-bit Temperature Resolution 0.01
  - ±0.4°C Temperature Accuracy
  - Integrated Heater
  - Low Power - 150μA active / 60nA standby 
 */
 
class SI7021 {
    public:
      SI7021( PinName sda, PinName scl, 
             int addr=SI7021_I2C_ADDR, int freq=100000 );
      ~SI7021(); 
      bool begin();
      bool read( float &temperature, float &humidity );
      void frequency( int freq );

    private:
      PinName _sda, _scl;
      int _addr;
      int _freq;
      uint8_t _buf[3];
      I2C *_i2c;
      uint8_t crc8( uint8_t data[], int len );
            
}; // end class

#endif // __SI7021_H
///////////////////////////////////////////////////////////////////////////////
