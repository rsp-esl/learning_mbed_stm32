//////////////////////////////////////////////////////////////////////////////
// Author: Rawat S. (KMUTNB, Bangkok/Thailand)
// Date: 2018-01-10
// Code Example: AnalogOut/DAC (Voltage-controlled LED dimming)
// Target Board: STM32 Nucleo L053R8
//////////////////////////////////////////////////////////////////////////////
#include "mbed.h"

const PinName AOUT_PIN = PA_4; //Nucleo L053R8: PA_4 / A2 pin !!!!
AnalogOut aout( AOUT_PIN );

int value = 0; // used to store the PWM duty cycle between 0..100
int pm = 1;    // count direction: 1 = Up or -1 = Down

int main() {
    while(1) {
      aout = value/255.0f;
      if ( value == 255 && pm == 1 ) {
         pm = -1; // decrement
      } else if ( value == 0 && pm == -1 ) {
         pm = 1;  // increment
      } 
      value += pm;   
      wait_ms(10); // delay for 10 ms
    }
}
//////////////////////////////////////////////////////////////////////////////
