#include <util/crc16.h>
#include <FastCRC.h>
FastCRC16 CRC16;
byte nibbleL;
byte nibbleH;
long crc=1;
byte buff[4];
long   reply;

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4); 
 void setup() {
 // delay(1500); 
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
}
void loop() {
  if(Serial.available()>0)
  {
   if (Serial.find('i'))
  {
   reply =  Serial . parseInt (); // we receive numerical value
   if(Serial.find('f'))
   {

 for(int i=3;i>=0;i--)
{
 nibbleL=reply%0x10;
 reply/=0x10;
 nibbleH=(reply%0x10);
 reply/=0x10;
nibbleH<<=4;
 buff[i]=nibbleH+nibbleL;
}
crc = CRC16.xmodem(buff, sizeof(buff));

lcd.setCursor(0,0);
for(int i=0 ;i<4;i++)
{
lcd.print(buff[i],HEX); 

  }
  buff[3]+=1;
 
if(crc==0)
{
lcd.setCursor(0,1);
lcd.print("true"); 
}
}
}
 // }
  }
}
