////////////////////////////////////////////////////////////////////////////
// Author: Rawat S. (KMUTNB, Bangkok/Thailand)
// Date: 2017-12-30
// Target board: STM32 Nucleo-32 L432KC
// Mbed OS version: 5.7
// Demo: PWM-based LED dimming (using PWM hardware)
////////////////////////////////////////////////////////////////////////////
#include "mbed.h"

PwmOut led( PA_11 ); // use a hardware-PWM pin, PA_11 / D10
// https://os.mbed.com/docs/v5.7/reference/pwmout.html

int value = 0; // used to store the PWM duty cycle between 0..100
int pm = 1; // 1 or -1

int main() {
   led.period_ms( 2 );  // peroid = 2 msec, freq = 500 Hz
   led = 0.0f;  // value between 0.0 to 1.0 (100% duty cycle)
   while(1) {
      if ( value == 255 && pm == 1 ) {
         pm = -1; // decrement
      } else if ( value == 0 && pm == -1 ) {
         pm = 1;  // increment
      }
      led = (value/255.0f); 
      value += pm;
      wait_ms( 5 );
   }
}
////////////////////////////////////////////////////////////////////////////
