#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
//#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
void setup() {
Serial.begin(1200);
Serial.setTimeout(50);  
pinMode(13,OUTPUT);
digitalWrite(13,LOW);
}
void loop() {
int state=  crc_16_data_14_rx();
if (state==1)
{
  lcd.setCursor(0,0);
lcd.print(state);
}
else if (state==0)
{
    lcd.setCursor(0,0);
lcd.print(state);
}

}
int crc_16_data_14_rx()
{
  long k=0;
int data[30];
long c;
long data2[30];  
int errt;
int corrt;
int comerr;
int state;
long corrdata;

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
  int n=29;
  int i=0;
  while(i<30 )
   {
 boolean b= bitRead(c,n);
 data[i]=b;
  n--;
       i++;
   }
     i =0; 
while (i<=29)
{
  if(i+16>29)
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
int t =29;
for (int i=0;i<=29;i++)
 {
   data2[i]=data[t];
   data2[i]<<=i;  
  
   td+=data2[i];
  t--;
  }
/*if (td==0)
{
corrt++;  
lcd.begin(16, 2);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Corrt:");
lcd.print(corrt,DEC);
lcd.setCursor(0,1);
lcd.print("data:");
lcd.print(c>>16);
delay(1000);
   }*/
/*else
{
  errt++;
lcd.begin(16, 2);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("errt:");
lcd.print(errt,DEC);
lcd.setCursor(0,1);
lcd.print("data:");
lcd.print(c>>16);
delay(1000);
}*/
   if (td==0)
   { 
    corrt++;  
//lcd.clear();
lcd.setCursor(0,1);
lcd.print("data:");
lcd.print(c>>16);
state=1;
return state;
   }  
else 
{
lcd.setCursor(0,0);
lcd.print("frame dropped");
lcd.print(corrt,DEC);
state=0;
return state;
}
/*
 errt++;
if (corrt>=2)
{
lcd.begin(16, 2);
//lcd.clear();
lcd.setCursor(0,0);
lcd.print("Corrt:");
lcd.print(corrt,DEC);
//lcd.setCursor(0,1);
//lcd.print("data:");
//lcd.print(c>>16);
delay(1000);
  }
/*else if (errt>=3&& errt<=5) 
{
  lcd.begin(16, 2);
//lcd.clear();
lcd.setCursor(0,0);
lcd.print("errt:");
lcd.print(errt,DEC);
//lcd.setCursor(0,1);
//lcd.print("data:");
//lcd.print(c>>16);
delay(1000);
}
*/
}
}
}
/*
if (errt==5)
{
  comerr++;
  lcd.clear();
lcd.setCursor(0,0);
lcd.print("packet dropped");
}
if (comerr==5)
{ 
comerr=0;
lcd.clear();
lcd.setCursor(0,0);
lcd.print("communication error");//we can use a special led for this type of error or use an lcd

  }
if ((errt+corrt)==5)
{
errt=0;
corrt=0;
}
*/
}    
