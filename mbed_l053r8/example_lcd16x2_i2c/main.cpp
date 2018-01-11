//////////////////////////////////////////////////////////////////////////////
// Author: Rawat S. (KMUTNB, Bangkok/Thailand)
// Date: 2018-01-11
// Code Example: LCD16x2 + I2C (PCF8574) Adapter
// Target Board: STM32 Nucleo L053R8
//////////////////////////////////////////////////////////////////////////////
#include "mbed.h"
#include "LiquidCrystal_I2C.h"

#define SCL_PIN        (PB_8)
#define SDA_PIN        (PB_9)
#define I2C_ADDR       (0x3F)

Serial pc( SERIAL_TX, SERIAL_RX, 115200 );
I2C   i2c( SDA_PIN, SCL_PIN );
LiquidCrystal_I2C lcd( I2C_ADDR, 16, 2 ); 

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

int main() {
  i2c.frequency( 400000 );
  i2c_scan();
  
  lcd.begin( &i2c );
  lcd.clear();
  lcd.setCursor(0,0); // set cursor at top-level position on the first row
  lcd.print( "ARM Mbed Demo" );
  lcd.setCursor(0,1); // set cursor at the start position on the second row
  lcd.print( "IoT @ KMUTNB" );
  wait_ms(5000);
 
  for (int i=0; i < 20; i++ ) {
    wait_ms( 500 );
    lcd.scrollDisplayRight();
  }

  uint16_t count = 0;
  char sbuf[20];
  lcd.clear();
  lcd.setCursor(0,0);
  while (1) {
     lcd.setCursor(0 /*col*/, 0 /*row*/); 
     sprintf( sbuf, "Count: %04d", count );
     lcd.print( sbuf );
     count = (count+1) % 10000;
     wait_ms( 1000 );
  }
}
//////////////////////////////////////////////////////////////////////////////
