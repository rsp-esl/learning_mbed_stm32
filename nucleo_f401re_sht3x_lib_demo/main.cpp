/////////////////////////////////////////////////////////////////////////
// Author: Rawat S. (KMUTNB, Bangkok/Thailand)
// Date: 2017-12-31
// Target board: STM32 Nucleo F401RE
// Mbed OS version 5.x
// Demo: Using the SHT3x library to read temperature and humidity values 
/////////////////////////////////////////////////////////////////////////
#include "mbed.h"
#include "SHT3x.h"

#define SCL_PIN  PB_8  // D15 pin on Nucleo F401RE board
#define SDA_PIN  PB_9  // D14 pin on Nucleo F401RE board

#define BAUDRATE  115200

Serial pc( USBTX, USBRX, BAUDRATE );
SHT3x sht31( SDA_PIN, SCL_PIN );

int main() {
    float temperature, humidity;    
    pc.printf( "Reading SHT3x-DIS temperature and humidity sensor...\n" );
    
    sht31.frequency( 400000 );
    if ( sht31.begin() ) {
       pc.printf( "Initializing SHT3x-DIS... OK\n" );
    } else {
       pc.printf( "Initializing SHT3x-DIS... FAILED !!!\n" );
    }
    
    while(1) {
       if ( sht31.read( temperature, humidity ) ) {
         pc.printf( "Temperature=%.1f deg.C, Humidity=%.1f %%RH\n", 
                     temperature, humidity );
       } else {
         pc.printf( "Sensor reading error !!!\n" );
       }
       wait(1.0); // 1 sec
    }
}
/////////////////////////////////////////////////////////////////////////
