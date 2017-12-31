////////////////////////////////////////////////////////////////////////////
// Author: Rawat S. (KMUTNB, Bangkok/Thailand)
// Date: 2017-12-30
// Target board: STM32 Nucleo-32 L432KC
// Mbed OS version: 5.7
// Demo: LED Dimming using DAC (Analog Output using the internal DAC)
////////////////////////////////////////////////////////////////////////////
#include "mbed.h"

#define DAC_OUT1  PA_4  // A3 pin
#define DAC_OUT2  PA_5  // A4 pin

#define BAUDRATE  115200

const PinName AOUT_PIN = DAC_OUT1;
AnalogOut aout( AOUT_PIN );
// see: https://os.mbed.com/docs/latest/reference/analogout.html

Serial pc( USBTX, USBRX, BAUDRATE ); // tx (PA_2), rx (PA_15)
// see: https://os.mbed.com/docs/latest/reference/serial.html

int value = 0; // used to store the PWM duty cycle between 0..100
int pm = 1;    // 1 or -1

int main() {
    pc.printf( "LED Dimming using DAC...\n" );
    while(1) {
      aout = value/255.0f;
      if ( value == 255 && pm == 1 ) {
         pm = -1; // decrement
      } else if ( value == 0 && pm == -1 ) {
         pm = 1;  // increment
      } 
      value += pm;   
      wait_ms(5); // delay for 5 ms
    }
}
