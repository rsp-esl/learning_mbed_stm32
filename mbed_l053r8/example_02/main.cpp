//////////////////////////////////////////////////////////////////////////////
// Author: Rawat S. (KMUTNB, Bangkok/Thailand)
// Date: 2018-01-10
// Code Example: LED + Push Button (active-low)
// Target Board: STM32 Nucleo L053R8
//////////////////////////////////////////////////////////////////////////////
#include "mbed.h"

DigitalOut led( PB_3 );    // specify the LED pin
DigitalIn  button( PB_4 ); // specify the button pin

int main() {
    button.mode( PullUp ); // enable internal pullup on button pin
    while (1) {
      led = !button; // invert the logic
    }
}
//////////////////////////////////////////////////////////////////////////////
