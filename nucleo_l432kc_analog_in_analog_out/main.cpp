////////////////////////////////////////////////////////////////////////////
// Author: Rawat S. (KMUTNB, Bangkok/Thailand)
// Date: 2017-12-30
// Target board: STM32 Nucleo-32 L432KC
// Mbed OS version: 5.7
// Demo: Analog In & Analog Out (ADC / DAC)
////////////////////////////////////////////////////////////////////////////
#include "mbed.h"

#define DAC_OUT1  PA_4  // A3 pin
#define DAC_OUT2  PA_5  // A4 pin

#define BAUDRATE  115200

const PinName AOUT_PIN = DAC_OUT1;
AnalogOut aout( AOUT_PIN );
// see: https://os.mbed.com/docs/latest/reference/analogout.html

const PinName AIN_PIN = PA_0;
AnalogIn ain( AIN_PIN );
// see: https://os.mbed.com/docs/latest/reference/analogin.html

Serial pc( USBTX, USBRX, BAUDRATE ); // tx (PA_2), rx (PA_15)
// see: https://os.mbed.com/docs/latest/reference/serial.html

int main() {
    pc.printf( "Nucleo L432KC: Analog In and Analog Out (ADC / DAC)...\n" );
    while(1) {
        aout.write( ain.read() );
        wait_ms( 100 ); // delay for 100 ms
    }
}
////////////////////////////////////////////////////////////////////////////
