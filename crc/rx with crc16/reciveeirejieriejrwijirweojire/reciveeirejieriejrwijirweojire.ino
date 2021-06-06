//#include <LiquidCrystal_I2C.h>
//#include <Wire.h>
//LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
long k=0;
int data[24];
long c;
long data2[24];  
void setup() {
Serial.begin(19200);
Serial.setTimeout(50);  
lcd.begin(16, 2);
pinMode(13,OUTPUT);
digitalWrite(13,LOW);
}
void loop() {
    if(Serial.available()>0)
   { 
    if (Serial.find("i"))
{
  c=  Serial . parseInt (); // we receive numerical value

 if (Serial.find("f"))
{
if (c==0)
{
  c++;
  }
  int n=23;
  int i=0;
  while(i<24 )
   {
 boolean b= bitRead(c,n);
 data[i]=b;
  n--;
       i++;
   }
     i =0; 
while (i<=23)
{
  if(i+16>23)
  {
    break;
    }
if (data [i]==1)
{
data[i]= !data[i];//x^16
data[i+4]=!data[i+4];//x^12
data[i+11]=!data[i+11];//x^5
data[i+16]=!data[i+16];//1  
}
i++;
}
long td=0;
int t =23;
for (int i=0;i<=23;i++)
 {
   data2[i]=data[t];
   data2[i]<<=i;  
  
   td+=data2[i];
  t--;
  }
if (td==0)
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("CRC:");
lcd.print(td,BIN);
lcd.setCursor(0,1);
lcd.print("data:");
lcd.print(c>>16);
   }
else
{

lcd.clear();
lcd.setCursor(0,0);
lcd.print("CRC:");
lcd.print(td,BIN);
lcd.setCursor(0,1);
lcd.print("data:");
lcd.print(c>>16);
}
}
   }
   }
   }    
