////////////////////////////////////////////////////////////////////////////
// Author: Rawat S. (KMUTNB, Bangkok/Thailand)
// Date: 2017-12-30
// Target board: STM32 Nucleo-32 L432KC
// Mbed OS version: 5.7
// Demo: Sleep and Wakeup Demo
////////////////////////////////////////////////////////////////////////////
#include "mbed.h"

#define BAUDRATE  115200

volatile bool sleep_state = false;
Serial pc( USBTX, USBRX, BAUDRATE ); // tx (PA_2), rx (PA_15)

InterruptIn btn( PB_4 ); // D12 pin (external push button, active-low)
DigitalOut led1( PB_3 ); // onboard USER1 LED
DigitalOut led2( PA_5 ); // A4 pin (additional LED)

int cnt = 0;

void irq_callback() {
    btn.disable_irq(); 
    sleep_state = !sleep_state;
}

int main() {
    btn.mode( PullUp );         // enable the internall pull-up resistor
    btn.fall( &irq_callback );  // trigger on falling edge
    btn.enable_irq();
    pc.printf( "Nucleo L432KC board: Sleep & Wakeup Demo...\n" );
        
    // note: 
    //  In the sleep mode, the LED2 will not toggle, both LED1 and LED2
    //  are turned off.
    //  To wake up the MCU, press the push button.
    while(1) {
        if ( sleep_state ) {
           led1 = led2 = 0;    // turn off LED1 and LED2
           btn.enable_irq();
           cnt++;
           sleep();
           wait_ms(100);
           btn.enable_irq();
           pc.printf( "Woken up from sleep, cnt: %d\n", cnt );
        } else {
           led1 = 1; // turn on LED1 
        }
        led2 = !led2;   // toggle LED2
        wait_ms( 100 );
    }
}
////////////////////////////////////////////////////////////////////////////
