//////////////////////////////////////////////////////////////////////////////
// Author: Rawat S. (KMUTNB, Bangkok/Thailand)
// Date: 2018-01-11
// Code Example: Interfacing with DHT22 (digital I/O)
// Target Board: STM32 Nucleo L053R8
//////////////////////////////////////////////////////////////////////////////
#include "mbed.h"
#include "DHT.h"  // use the 'DHT' library

const PinName DATA_PIN = D5;

Serial pc( SERIAL_TX, SERIAL_RX, 115200 );
DHT dht( DATA_PIN ); // Data Pin of the DHT22 sensor (use Vcc=+3.3V)

int main() {
    float temperature, humidity;
    pc.printf( "ARM MBed + Nucleo STM32 + DHT demo...\r\n" );
    wait(0.5);
    while(1) {
      if ( dht.read( temperature, humidity ) ) {
         pc.printf( "Temperature=%.1f deg.C, Humidity=%.1f %%RH\r\n", 
                     temperature, humidity );
      } else {
         pc.printf( "%02X\r\n", dht.get_error() );
         pc.printf( "DHT2x read error!!! \r\n" );
      }
      wait_ms(1000);
    }
}
//////////////////////////////////////////////////////////////////////////////
