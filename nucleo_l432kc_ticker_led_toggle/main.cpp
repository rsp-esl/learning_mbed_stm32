////////////////////////////////////////////////////////////////////////////
// Author: Rawat S. (KMUTNB, Bangkok/Thailand)
// Date: 2017-12-30
// Target board: STM32 Nucleo-32 L432KC
// Mbed OS version: 5.7
// Demo: LED toggle using Tickers
////////////////////////////////////////////////////////////////////////////
#include "mbed.h"

DigitalOut led1( PB_3 ); 
DigitalOut led2( PA_11 );

Ticker ticker1, ticker2;
// see: https://os.mbed.com/docs/v5.7/reference/ticker.html

void led1_toggle() {
    led1 = !led1;
}

void led2_toggle() {
    led2 = !led2;
}

int main() {
    led1 = 0;
    led2 = 0;
    ticker1.attach( &led1_toggle, 0.1 ); // callback every 0.1 seconds 
    ticker2.attach( &led2_toggle, 0.5 ); // callback every 0.5 seconds
    
    while(1) {
        wait_ms(10);
    }
}
////////////////////////////////////////////////////////////////////////////
