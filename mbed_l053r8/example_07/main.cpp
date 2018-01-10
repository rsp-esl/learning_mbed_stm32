//////////////////////////////////////////////////////////////////////////////
// Author: Rawat S. (KMUTNB, Bangkok/Thailand)
// Date: 2018-01-10
// Code Example: Interfacing with a Rotary Encoder 
// Target Board: STM32 Nucleo L053R8
//////////////////////////////////////////////////////////////////////////////
#include "mbed.h"

// PB_5, PB_4, // Nucleo L053R8 D4, D5
#define QA_PIN  PB_5
#define QB_PIN  PB_4

Serial pc( SERIAL_TX, SERIAL_RX, 115200 );
InterruptIn qa_pin( QA_PIN );   // CLK
DigitalIn   qb_pin( QB_PIN );   // DT

volatile int last_a = 1, last_b = 1;
volatile bool encoder_update = false;
volatile int16_t encoder_cnt = 0;

void encode_inputs() {
  qa_pin.disable_irq();
  int a = qa_pin.read();
  int b = qb_pin.read();
  if ( (a != last_a) || (b != last_b) ) {
    if ( a == b ) {
       encoder_cnt++;
    } else { 
       encoder_cnt--;
    }
    encoder_update = true;
    last_a = a;
    last_b = b;
  }
  qa_pin.enable_irq();
}

int main() {
   // qa_pin.mode( PullUp ); 
   // qb_pin.mode( PullUp );  
   qa_pin.fall( &encode_inputs ); 
   qa_pin.rise( &encode_inputs ); 
   qa_pin.enable_irq();  
   pc.printf( "Rotary Encoder Reading Demo\r\n" );
   while(1) {
     if ( encoder_update ) {
       encoder_update = false;
       pc.printf( "Encoder Counter: %d\r\n", encoder_cnt );
     }
   }
}
//////////////////////////////////////////////////////////////////////////////
