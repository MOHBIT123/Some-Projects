#include <util/crc16.h>
#include <FastCRC.h>
FastCRC16 CRC16;
byte nibbleL=0;
byte nibbleH=0;
 void setup() {
 // delay(1500); 
  Serial.begin(9600);
}
void loop() {
/*Serial.print('i');
Serial.print(0x10202711);
Serial.print('f');
*/
  uint32_t crc;
   uint8_t buf[2]; //= {0x10,0x20};//we enter data one byte at a time since here the used algorithm is used to calculate crc with ascii letters which represent each letter in one unsigned byte  
  buf[0]=0x10;
  buf[1]=0x20;
 crc = CRC16.xmodem(buf, sizeof(buf));
 uint32_t crc1=crc;
 uint32_t td=0x1020;
 td<<=16;
 td+=crc1;
Serial.print('i');
Serial.print(td);
Serial.print('f');
/*
uint8_t buff[4];
 for(int i=3;i>=0;i--)
{
 nibbleL=td%0x10;
 td/=0x10;
 nibbleH=(td%0x10);
 td/=0x10;
nibbleH<<=4;
 buff[i]=nibbleH+nibbleL;
Serial.println(td,HEX);
//Serial.println(nibbleL,HEX);
}
/*
 for(int i=0;i<4;i++)
{
Serial.println(buff[i],HEX);
//Serial.println(nibbleL,HEX);
}
//buff[3]+=1;
crc = CRC16.xmodem(buff, sizeof(buff));
if(crc==0)
Serial.println("true");
delay(100);*/
}
