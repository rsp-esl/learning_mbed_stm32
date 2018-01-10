//////////////////////////////////////////////////////////////////////////////
// Author: Rawat S. (KMUTNB, Bangkok/Thailand)
// Date: 2018-01-10
// Code Example: LED + Push Button (active-low) with External Interrupt
// Target Board: STM32 Nucleo L053R8
//////////////////////////////////////////////////////////////////////////////
#include "mbed.h"

DigitalOut  led( PB_3 );     // digital output pin
InterruptIn button( PB_4 );  // digital input pin with ext. interrupt enabled

volatile bool changed = false;

void irq_callback() {
   button.disable_irq();
   changed = true;
}

int main() {
  button.fall( &irq_callback ); // detect falling-edge 
  button.mode( PullUp );  // enable internal pull-up resistor 
  button.enable_irq();    // enable interrupt
  while(1) {
    if ( changed ) {
       led = !led; // toggle and update LED output    
       changed = false;
       wait_ms(50);
       button.enable_irq();
     }
     wait_ms( 10 );
  }
}
//////////////////////////////////////////////////////////////////////////////
