////////////////////////////////////////////////////////////////////////////
// Author: Rawat S. (KMUTNB, Bangkok/Thailand)
// Date: 2017-12-30
// Target board: STM32 Nucleo-32 L432KC
// Mbed OS version: 5.7
// Demo: Reading data from the SHT3x-DIS temperature & humidity sensor over I2C 
////////////////////////////////////////////////////////////////////////////
#include "mbed.h"

#define SHT3x_I2C_ADDR         (0x44)  // SHT3x-DIS (I2C)

#define SHT3x_SOFT_RESET       (0x30A2)
// single shot mode, no clock stretching
#define SHT3x_ACCURACY_HIGH    (0x2C06)
#define SHT3x_ACCURACY_MEDIUM  (0x2C0D)
#define SHT3x_ACCURACY_LOW     (0x2C10)

#define SCL_PIN  PB_6  // D5
#define SDA_PIN  PB_7  // D4
#define BAUDRATE  115200

Serial pc( USBTX, USBRX, BAUDRATE ); // tx (PA_2), rx (PA_15)
// see: https://os.mbed.com/docs/latest/reference/serial.html

I2C i2c( SDA_PIN, SCL_PIN );
// see: https://os.mbed.com/docs/latest/reference/i2c.html

const int addr = (SHT3x_I2C_ADDR << 1);

float temp, humid;
 
// CRC-8, Polynomial: 0x31  x^8 + x^5 + x^4 + 1, Initial value = 0xff
uint8_t CRC8( const uint8_t *data, int len ) {
  uint8_t crc = 0xFF;
  for ( int i=0; i < len; i++ ) {
    crc ^= data[i];
    for ( int j=0; j < 8; j++ ) {
      crc = crc & 0x80 ? (crc << 1) ^ 0x31 : crc << 1;
    }
  }
  return crc;
}

bool sht3x_init() {
  int ack;
  uint8_t buf[2];
  buf[0] = (SHT3x_SOFT_RESET >> 8) & 0xff;
  buf[1] = SHT3x_SOFT_RESET & 0xff;
  ack = i2c.write( addr, (const char *)buf, 2 ); 
  if ( ack != 0 ) { // no ACK
    return false;
  }
  wait_ms(10);

  buf[0] = (SHT3x_ACCURACY_HIGH >> 8) & 0xff;
  buf[1] = SHT3x_ACCURACY_HIGH & 0xff;
  ack = i2c.write( addr, (const char *)buf, 2 ); 
  if ( ack != 0 ) { // no ACK
    return false;
  }
  return true;
}

bool sht3x_read_sensor() {
  int ack;
  uint8_t buf[2]; 
  // Send measurement command
  buf[0] = (SHT3x_ACCURACY_HIGH >> 8) & 0xff;
  buf[1] = SHT3x_ACCURACY_HIGH & 0xff; 
  ack = i2c.write( addr, (const char *)buf, 2 ); 
  if ( ack != 0 ) { // no ACK
     return false;
  }
  wait_ms(50); // note: measurement time is about 15 msec
  
  uint8_t rdata[6];
  ack = i2c.read( addr, (char *)rdata, 6 );
  if ( ack != 0 ) { // no ACK
     return false;
  }

#ifdef DEBUG
  for ( int i=0; i < 6; i++ ) {
     pc.printf( "%02X ", rdata[i] );     
  }  
  pc.printf("\n");
#endif

  // check CRC for both values
  if ( CRC8(rdata,2)==rdata[2] && CRC8(rdata+3,2)==rdata[5] ) {
    uint16_t value;
    value = (rdata[0] << 8) + rdata[1];
    temp  = ((value * 175.0) / 65535) - 45; // temperature in Celsius.
    value = (rdata[3] << 8) + rdata[4];
    humid = ((value * 100.0) / 65535); // relative humidity
    return true;
  } 
  return false;  
}

int main() {
    i2c.frequency( 400000 );
    sht3x_init();  // initialize the SHT3x-DIS sensor
    pc.printf( "Reading SHT3x-DIS temperature and humidity sensor...\n" );
    
    while(1) {
      if ( sht3x_read_sensor() ) {
          pc.printf( "Read: %.1f deg.C, %.1f %%RH \n", temp, humid );
       } else {
          pc.printf( "Sensor reading error !!!\n" );
       }
       wait(1.0); // 1 sec
    }
}
////////////////////////////////////////////////////////////////////////////
