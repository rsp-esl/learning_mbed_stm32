//////////////////////////////////////////////////////////////////////////////
// Author: Rawat S. (KMUTNB, Bangkok/Thailand)
// Date: 2018-01-11
// Code Example: Sleep & Wakeup (Activated by External Interrupt)
// Target Board: STM32 Nucleo L053R8
//////////////////////////////////////////////////////////////////////////////
#include "mbed.h"

#define BAUDRATE  115200

volatile bool sleep_state = false;
Serial pc( SERIAL_TX, SERIAL_RX, BAUDRATE ); 

InterruptIn btn( PB_3 ); 
DigitalOut led1( PB_4 ); 
DigitalOut led2( PB_5 ); 

void irq_callback() {
    btn.disable_irq(); 
    sleep_state = !sleep_state;
}

int main() {
    btn.mode( PullUp );         // enable the internall pull-up resistor
    btn.fall( &irq_callback );  // trigger on falling edge
    btn.enable_irq();
    while(1) {
        if ( sleep_state ) {   // enter sleep mode
           led1 = led2 = 0;    // turn off LED1 and LED2
           btn.enable_irq();
           sleep();
           wait_ms(10);
           btn.enable_irq();
           pc.printf( "Woken up from sleep\r\n" );
        } else {
           led1 = 1; // turn on LED1 
        }
        led2 = !led2;   // toggle LED2
        wait_ms( 100 );
    }
}
//////////////////////////////////////////////////////////////////////////////
