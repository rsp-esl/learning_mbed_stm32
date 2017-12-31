/////////////////////////////////////////////////////////////////////////
// Author: Rawat S. (KMUTNB, Bangkok/Thailand)
// Date: 2017-12-31
// Target board: STM32 Nucleo F401RE
// Mbed OS version 5.x
/////////////////////////////////////////////////////////////////////////
#include "mbed.h"
#include "DHT2x.h"

#define BAUDRATE  115200
#define DATA_PIN  PB_4  // D5 pin on Nucleo F401RE

Serial pc( USBTX, USBRX, BAUDRATE ); 

DHT2x dht22( DATA_PIN );

int main() {
    float temperature, humidity;
    pc.printf( "Nucleo F401RE - DHT2x demo...\n" );
    while(1) {
      if ( dht22.read( temperature, humidity ) ) {
         pc.printf( "Temperature=%.1f deg.C, Humidity=%.1f %%RH\n", 
                     temperature, humidity );
      } else {
         pc.printf( "DHT2x read error!!!\n" );
      }
      wait_ms(1000);
    }
}
/////////////////////////////////////////////////////////////////////////
