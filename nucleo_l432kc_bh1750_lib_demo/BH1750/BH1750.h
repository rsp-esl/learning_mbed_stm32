/////////////////////////////////////////////////////////////////////////
#ifndef __BH1750_H
#define __BH1750_H

#include "mbed.h"

#define BH1750_I2C_ADDR            (0x23) 
#define BH1750_CONT_HIGH_RES_MODE  (0x10)

// a very simple BH1750 class
class BH1750 {
  public:
    BH1750( I2C *i2c, uint8_t addr=BH1750_I2C_ADDR );
    bool init();
    int read();
 
  private:
    I2C      *_i2c;
    uint8_t _addr;
};
 
#endif // __BH1750_H
/////////////////////////////////////////////////////////////////////////
