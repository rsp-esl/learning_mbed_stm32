#ifndef __DHT2x_H
#define __DHT2x_H

#include "mbed.h"

class DHT2x {
    public:
      DHT2x( PinName pin );
      ~DHT2x(); 
      void begin();
      bool read( float &temperature, float &humidity );

    private:
      PinName _pin;
      uint8_t _error;
      uint8_t _buf[5];
      DigitalInOut *_dio;
      
      bool read_byte( uint8_t &value );
      inline bool is_data_high() { return (_dio->read()==1); }
      inline bool is_data_low()  { return (_dio->read()==0); }
      inline void data_high()    { _dio->write(1);  }
      inline void data_low()     { _dio->write(0);  }
      inline void data_input()   { _dio->input();   }
      inline void data_output()  { _dio->output();  }
      
}; // end class

#endif // __DHT2x_H
///////////////////////////////////////////////////////////////////////////////
