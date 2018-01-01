#include "mbed.h"

#define BAUDRATE         115200

Serial pc( SERIAL_TX, SERIAL_RX, BAUDRATE );
// see: https://os.mbed.com/docs/latest/reference/serial.html

Ticker ticker;
DigitalOut led(LED1);

volatile bool update_flag = true;

void update_callback(void) {
   update_flag = true;
}
 
int main(void) {
   uint32_t cnt = 1;
   led = 0;
   ticker.attach( &update_callback, 5 ); // update every 5 seconds
   pc.printf( "Sleep and Wakeup with Ticker....\n" );

   while(1) {
      if ( update_flag ) {
         led = 1;
         update_flag = false;
         pc.printf( "Wakeup...#%d\n", cnt++ );
         wait_ms(10);
         led = 0;
         sleep();
      }
      else {
         led = !led;
         wait_ms(100);
      }
    }
}
