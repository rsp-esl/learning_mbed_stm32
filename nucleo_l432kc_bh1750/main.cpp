////////////////////////////////////////////////////////////////////////////
// Author: Rawat S. (KMUTNB, Bangkok/Thailand)
// Date: 2017-12-30
// Target board: STM32 Nucleo-32 L432KC
// Mbed OS version: 5.7
// Demo: Reading sensor data from the BH1750 light sensor over I2C 
////////////////////////////////////////////////////////////////////////////
#include "mbed.h"

#define BH1750_I2C_ADDR            (0x23) 
#define BH1750_CONT_HIGH_RES_MODE  (0x10)

#define SCL_PIN          PB_6  // D5
#define SDA_PIN          PB_7  // D4
#define BAUDRATE         115200

Serial pc( USBTX, USBRX, BAUDRATE ); // tx (PA_2), rx (PA_15)
// see: https://os.mbed.com/docs/latest/reference/serial.html

I2C i2c( SDA_PIN, SCL_PIN );
// see: https://os.mbed.com/docs/latest/reference/i2c.html

const int addr = (BH1750_I2C_ADDR << 1);

bool bh1750_init() {
   int ack;
   uint8_t buf[2];
   buf[0] = BH1750_CONT_HIGH_RES_MODE;
   ack = i2c.write( addr, (const char *)buf, 1 );
   wait_ms(10);
   if ( ack != 0 ) { // no ACK
      return false;
   }
   return true;
}

float bh1750_read() {
   int ack;
   uint8_t buf[2];
   
   ack = i2c.read( addr, (char *)buf, 2 );
   if ( ack != 0 ) {
       return -1.0f;
   }
   uint16_t level = buf[0];
   level = (level << 8) | buf[1];
   return (level/1.2f); // Convert raw value to lux
}

int main() {
    float lux;
    i2c.frequency( 400000 );
    bh1750_init();  // initialize the  sensor
    pc.printf( "Reading BH1750 light sensor...\n" );
    while(1) {
       lux = bh1750_read();
       if ( lux > 0 ) {
          pc.printf( "Read: %d Lux\n", (int)lux );
       } else {
          pc.printf( "Sensor reading error !!!\n" );
       }
       wait(1.0); // 1 sec
    }
}
////////////////////////////////////////////////////////////////////////////
