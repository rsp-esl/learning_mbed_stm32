#include "mbed.h"

#define TRIG_PIN   D4   // Output
#define ECHO_PIN   D5   // Input
Serial pc( SERIAL_TX, SERIAL_RX, 115200 );
DigitalIn echo( ECHO_PIN );
DigitalOut trig( TRIG_PIN );
Timer timer;

const float sound_speed  = 34300;     // in cm/s

float measure() {
   trig = 1;
   wait_us( 20 );
   trig = 0;
   while ( echo == 0 ) { wait_us(10); } // wait for rising edge
   timer.reset();  // reset timer
   while ( echo == 1 ) { wait_us(10); } // wait for falling edge
   uint32_t duration_us = timer.read_us();
   float distance = (sound_speed * duration_us)/(1000000*2);
   return distance;
}

int main() {
   timer.start();  // start timer
   while(1) {
     float distance = measure();
     if (distance > 5000) 
        pc.printf( "Distance: Out of range !!!\r\n" );
     else       
        pc.printf( "Distance: %.1f cm\r\n", distance );
     wait_ms(500);
   }
}

//////////////////////////////////////////////////////////////////////////
// t = (2*d)/v ; t = time duration, d = distance, v = sound speed
// => d = v*t/2 
//      = ( 343 [m/s] * t [s] )/ 2
//      = ( 34300 [cm/s] * t [s] )/ 2
//      = (34300 [cm/s] * t [usec]/10^6)/ / 2
//////////////////////////////////////////////////////////////////////////

