/////////////////////////////////////////////////////////////////////////
// Author: Rawat S. (KMUTNB, Bangkok/Thailand)
// Date: 2017-12-31
// Target board: STM32 Nucleo L432KC
// Mbed OS version 5.x
/////////////////////////////////////////////////////////////////////////
#include "mbed.h"    // import the mbed library
#include "BH1750.h"  // import the BH1750 library

#define SCL_PIN          PB_6  // D5
#define SDA_PIN          PB_7  // D4
#define BAUDRATE         115200

Serial pc( USBTX, USBRX, BAUDRATE ); // tx (PA_2), rx (PA_15)
// see: https://os.mbed.com/docs/latest/reference/serial.html

I2C i2c(SDA_PIN, SCL_PIN);
BH1750 bh1750( &i2c, 0x23 );   // create an BH1750 instance

int main() {
   int lux;
   i2c.frequency( 400000 ); // set I2C clock frequency
   if ( bh1750.init() ) {
       pc.printf( "BH1750 initialization OK...\n" );
   }   
   while(1) {
       lux = bh1750.read(); // read the light intensity
       if ( lux >= 0 ) {
          pc.printf( "Read: %d Lux\n", lux );
       } else {
          pc.printf( "Sensor reading error !!!\n" );
       }
       wait(1.0); // 1 sec
    }
}
/////////////////////////////////////////////////////////////////////////
