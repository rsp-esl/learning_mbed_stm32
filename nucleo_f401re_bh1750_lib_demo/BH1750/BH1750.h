#ifndef __BH1750_H
#define __BH1750_H

#include "mbed.h"

/////////////////////////////////////////////////////////////////////////

// BH1750 Default Address
#define BH1750_I2CADDR                     0x23

// Power off the BH1750 device
#define BH1750_POWER_DOWN                  0x00

// Power on the BH1750 device
#define BH1750_POWER_ON                    0x01

// Reset data register value
#define BH1750_RESET                       0x07

//// Continuous mode measurement mode

// Start measurement at 1.0 Lux
// Measurement time is approx 120ms.
#define BH1750_CONT_HIGH_RES_MODE          0x10

// Start measurement at 0.5 Lux resolution
// Measurement time is approx 120ms.
#define BH1750_CONT_HIGH_RES_MODE_2        0x11

// Start measurement at 4.0 Lux resolution 
// Measurement time is approx 16ms.
#define BH1750_CONT_LOW_RES_MODE           0x13

//// Single-shot mode measurement mode (automatic power down after measurement)

// Start measurement at 1.0 Lux resolution 
//Measurement time is approx 120ms.
#define BH1750_ONE_TIME_HIGH_RES_MODE      0x20

// Start measurement at 0.5 Lux resolution
// Measurement time is approx 120ms.
#define BH1750_ONE_TIME_HIGH_RES_MODE_2    0x21

// Start measurement at 1.0 Lux resolution. 
// Measurement time is approx 120ms.
#define BH1750_ONE_TIME_LOW_RES_MODE       0x23

/////////////////////////////////////////////////////////////////////////

class BH1750 {
public:
    BH1750( PinName sda, PinName scl, 
            uint8_t addr=BH1750_I2CADDR, uint32_t freq_hz=100000 );
    ~BH1750();
    bool begin( uint8_t measure_mode=BH1750_ONE_TIME_HIGH_RES_MODE  );
    void frequency( uint32_t freq_hz );
    bool mode( uint8_t measure_mode );
    bool read( float & intensity );
    void reset();
    void power_on();
    void power_down();
    inline bool is_error() { return (_status != 0); }

private:
    I2C *     _i2c;
    PinName   _sda, _scl;
    uint8_t   _addr;
    uint8_t   _mode;
    uint8_t   _buf[2];
    int       _status;
    bool write_reg( uint8_t data );
    bool read_reg( uint8_t &data );
    bool read_raw( uint16_t &data );
};

#endif // __BH1750_H

/////////////////////////////////////////////////////////////////////////

