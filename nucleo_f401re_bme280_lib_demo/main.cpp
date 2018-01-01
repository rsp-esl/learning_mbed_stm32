/////////////////////////////////////////////////////////////////////////
// Author: Rawat S. (KMUTNB, Bangkok/Thailand)
// Date: 2018-01-01
// Target board: STM32 Nucleo F401RE
// Mbed OS version 5.x
// Demo: Reading data from BME280 sensor module over I2C bus

/////////////////////////////////////////////////////////////////////////
#include "mbed.h"    // import the mbed library
#include "BME280.h"  // import the BME280 library

#define SCL_PIN  PB_8  // D15 pin on Nucleo F401RE board
#define SDA_PIN  PB_9  // D14 pin on Nucleo F401RE board

#define BAUDRATE         115200

Serial pc( USBTX, USBRX, BAUDRATE );
// see: https://os.mbed.com/docs/latest/reference/serial.html

BME280 bme280( SDA_PIN, SCL_PIN ); 

int main() {
   float temperature, humidity, pressure;
   
   bme280.frequency( 400000 );
   if ( bme280.begin() ) {
       pc.printf( "BME280 initialization OK...\n" );
       pc.printf( "BME280 Chip ID: 0x%02X\n", bme280.read_chip_id() );
   } else {
       pc.printf( "BME280 initialization FAILED !!!\n" );
   }
   
   while(1) {
       if ( bme280.read( temperature, humidity, pressure ) ) {
         pc.printf( "%.1f deg.C, %.1f %%RH, %.2f hPa\n", 
                    temperature, humidity, pressure/100 );
       } else {
         pc.printf( "BME280 sensor reading error !!! \n" );
       }
       wait(1.0f); // 1.0 second
    }
}
/////////////////////////////////////////////////////////////////////////
