////////////////////////////////////////////////////////////////////////////
// Author: Rawat S. (KMUTNB, Bangkok/Thailand)
// Date: 2017-12-30
// Target board: STM32 Nucleo-32 L432KC
// Mbed OS version: 5.7
// Demo: Reading multiple analog inputs
////////////////////////////////////////////////////////////////////////////
#include "mbed.h"

#define BAUDRATE         115200
Serial pc( USBTX, USBRX, BAUDRATE ); // tx (PA_2), rx (PA_15)
// see: https://os.mbed.com/docs/latest/reference/serial.html

#define NUM_CHANNELS   7

const PinName AIN_PINS[] = { 
   PA_0, PA_1, PA_3, PA_4, PA_5, PA_6, PA_7 // A0, A1, A2, A3, A4, A5, A6
}; 

AnalogIn *channels[ NUM_CHANNELS ];
// https://os.mbed.com/docs/latest/reference/analogin.html

int main() {
    for ( int i=0; i < NUM_CHANNELS; i++ ) {
      channels[i] = new AnalogIn( AIN_PINS[i] );
    }
    pc.printf( "Nucleo L432KC - ADC reading...\n\n" );
    while(1) {
      char ch;
      float volt;
      for ( int i=0; i < NUM_CHANNELS; i++ ) {
         ch = (i==(NUM_CHANNELS-1)) ? '\n' : ',';
         volt = (3.3f * channels[i]->read());
         pc.printf( "A%d=[%.3f]%c", i, volt, ch );
      }
      pc.printf("\n");
      wait(2.0); // delay for 2 seconds
    }
}
////////////////////////////////////////////////////////////////////////////
