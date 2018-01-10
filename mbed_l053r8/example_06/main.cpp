//////////////////////////////////////////////////////////////////////////////
// Author: Rawat S. (KMUTNB, Bangkok/Thailand)
// Date: 2018-01-10
// Code Example: LED Blink with Timer-based Ticker 
// Target Board: STM32 Nucleo L053R8
//////////////////////////////////////////////////////////////////////////////
#include "mbed.h"

DigitalOut led1( PB_5 );
DigitalOut led2( PB_4 );
Ticker ticker1, ticker2;

void led1_toggle() { led1 = !led1; }
void led2_toggle() { led2 = !led2; }

int main() {
    led1 = 0;
    led2 = 0;
    ticker1.attach( &led1_toggle, 0.1 ); // callback every 0.1 seconds 
    ticker2.attach( &led2_toggle, 0.5 ); // callback every 0.5 seconds
    while(1) {
        wait_ms(10);
    }
}
//////////////////////////////////////////////////////////////////////////////
