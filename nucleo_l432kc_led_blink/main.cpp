////////////////////////////////////////////////////////////////////////////
// Author: Rawat S. (KMUTNB, Bangkok/Thailand)
// Date: 2017-12-30
// Target board: STM32 Nucleo-32 L432KC
// Mbed OS version: 5.7
// Demo: LED blink
////////////////////////////////////////////////////////////////////////////
#include "mbed.h"

const int DELAY_MS = 100; // msec

DigitalOut led( PB_3 ); // use on-board LED (LED1)

int state = 0;

int main() {
    while(1) { // endless loop
        led = state;           // update LED output
        state ^= 1;            // toggle state
        wait_ms( DELAY_MS );   // delay in msec
    }
}
////////////////////////////////////////////////////////////////////////////
