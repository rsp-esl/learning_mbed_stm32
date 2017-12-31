////////////////////////////////////////////////////////////////////////////
// Author: Rawat S. (KMUTNB, Bangkok/Thailand)
// Date: 2017-12-30
// Target board: STM32 Nucleo-32 L432KC
// Mbed OS version: 5.7
// Demo: LED toggle when pressing the push button
////////////////////////////////////////////////////////////////////////////
#include "mbed.h"

DigitalOut led( PB_3 );
// see: https://os.mbed.com/docs/v5.7/reference/digitalout.html

InterruptIn button( PB_4 ); 
// see: https://os.mbed.com/docs/v5.7/reference/interruptin.html

volatile bool changed =  false;

void irq_callback() {
   button.disable_irq();
   changed = true;
}

int main() {
  button.fall( &irq_callback ); // set callback for falling-edge ext.interrupt
  button.mode( PullUp ); // enable internal pull-up on the input button pin
  button.enable_irq();
  while(1) {
    if ( changed ) {
       led = !led; // toggle and update LED output    
       changed = false;
       button.enable_irq();
     }
     wait_ms( 10 );
  }
}
////////////////////////////////////////////////////////////////////////////
