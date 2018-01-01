/////////////////////////////////////////////////////////////////////////
// Author: Rawat S. (KMUTNB, Bangkok/Thailand)
// Date: 2018-01-01
// Target board: STM32 Nucleo L432KC
// Mbed OS version 5.x
/////////////////////////////////////////////////////////////////////////
#include "mbed.h"    // import the mbed library
#include "BH1750.h"  // import the BH1750 library

#define SCL_PIN  PB_8  // D15 pin on Nucleo F401RE board
#define SDA_PIN  PB_9  // D14 pin on Nucleo F401RE board

#define BAUDRATE         115200

Serial pc( USBTX, USBRX, BAUDRATE );
// see: https://os.mbed.com/docs/latest/reference/serial.html

BH1750 bh1750( SDA_PIN, SCL_PIN );   // create an BH1750 instance

int main() {
   float intensity;
   
   if ( bh1750.begin() ) {
       pc.printf( "BH1750 initialization OK...\n" );
   } else {
       pc.printf( "BH1750 initialization FAILED !!!\n" );
   }
   while(1) {
       if ( bh1750.read( intensity ) ) {
         pc.printf( "%.1f Lux\n", intensity );
       } else {
         pc.printf( "BH1750 sensor reading error\n" );
       }
       wait(0.5); // 0.5 seconds
    }
}
/////////////////////////////////////////////////////////////////////////
