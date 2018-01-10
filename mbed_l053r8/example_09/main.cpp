#include "mbed.h"

// Nucleo L053R8: PA_4 / A2 pin, PA_2 = A0 pin
const PinName AOUT_PIN = PA_4;
const PinName AIN_PIN  = PA_0; 

AnalogIn  ain( AIN_PIN );
AnalogOut aout( AOUT_PIN );
Serial pc( SERIAL_TX, SERIAL_RX, 115200 );

int main() {
    uint16_t value;
    while(1) {
      value = ain.read_u16(); // value
      pc.printf( "%u\r\n", value );
      aout.write_u16( value );
      wait_ms(100); // delay for 100 ms
    }
}
