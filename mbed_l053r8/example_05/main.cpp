//////////////////////////////////////////////////////////////////////////////
// Author: Rawat S. (KMUTNB, Bangkok/Thailand)
// Date: 2018-01-10
// Code Example: RGB LED Demo
// Target Board: STM32 Nucleo L053R8
//////////////////////////////////////////////////////////////////////////////
#include "mbed.h"

BusOut rgb( PB_5, PB_4, PB_10 ); // Nucleo L053R8 D4, D5, D6

int main() {
    uint8_t value = 1;
    while(1) {
        rgb = ~value; // invert the logic (for active-low RGB LED)
        // Rotate shift-left
        value = ((value << 1) | (value >> 2)) & 0b111;
        wait_ms(500);
    }
}
//////////////////////////////////////////////////////////////////////////////
