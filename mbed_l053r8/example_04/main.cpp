//////////////////////////////////////////////////////////////////////////////
// Author: Rawat S. (KMUTNB, Bangkok/Thailand)
// Date: 2018-01-10
// Code Example: PWM-based LED Dimming
// Target Board: STM32 Nucleo L053R8
//////////////////////////////////////////////////////////////////////////////
#include "mbed.h"

PwmOut led( PB_3 );  // use a hardware-PWM pin
int value = 0;       // used to store the PWM duty cycle between 0..100
int pm = 1;          // count direction: 1 (up) or -1 (down)

int main() {
   led.period_ms( 2.0 );  // period = 2 msec, freq = 500 Hz
   led = 0.0f;  // value between 0.0 to 1.0 (100% duty cycle)
   while(1) {
      if ( value == 255 && pm == 1 ) { pm = -1; }     // change to decrement
      else if ( value == 0 && pm == -1 ) { pm = 1; }  // change to increment
      led = (value/255.0f);    // update the PWM output value
      value += pm;
      wait_ms( 5 );
   }
}
//////////////////////////////////////////////////////////////////////////////
