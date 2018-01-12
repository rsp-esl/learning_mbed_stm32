//////////////////////////////////////////////////////////////////////////////
// Author: Rawat S. (KMUTNB, Bangkok/Thailand)
// Date: 2018-01-11
// Code Example: Interfacing with BH1750 Light Sensor via I2C
// Target Board: STM32 Nucleo L053R8
//////////////////////////////////////////////////////////////////////////////
#include "mbed.h"

#define SCL_PIN        (PB_8)
#define SDA_PIN        (PB_9)
#define I2C_ADDR       (0x23)

const uint8_t addr = (I2C_ADDR << 1);
const uint8_t BH1750_CONT_HIGH_RES_MODE = (0x10);

Serial pc( SERIAL_TX, SERIAL_RX, 115200 );
I2C    i2c( SDA_PIN, SCL_PIN );

void i2c_scan() {
  uint8_t data=0;  
  int found_devices = 0;
  pc.printf("Scan I2C devices....\r\n" );
  for ( uint8_t addr=1; addr <= 0x7f; addr++ ) {
     int ack = i2c.write( (addr << 1), (const char *)&data, 1 );
     if (ack == 0) {
         pc.printf("Found device @ 0x%02X\r\n", addr );
         found_devices++;
     }
  }
  if ( found_devices > 0 ) {
    pc.printf("Total number I2C devices found: %d\r\n", found_devices );
  } else {
    pc.printf("No device found \r\n" );
  }   
}

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
    i2c_scan();
    bh1750_init();  // initialize the  sensor
    pc.printf( "Reading BH1750 light sensor...\r\n" );
    while(1) {
       lux = bh1750_read();
       if ( lux > 0 ) {
          pc.printf( "Read: %d Lux\r\n", (int)lux );
       } else {
          pc.printf( "Sensor reading error !!!\r\n" );
       }
       wait(1.0); // 1 sec
    }
}
//////////////////////////////////////////////////////////////////////////////
