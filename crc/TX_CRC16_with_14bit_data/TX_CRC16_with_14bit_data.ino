#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
//#include <LiquidCrystal.h>
int c;
// initialize the library with the numbers of the interface pins
//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
void  setup ()
{ 
  Serial . begin (1200);

} 
void  loop ()
{
  crc_16_data_14_tx(16383);
} 
void crc_16_data_14_tx(long c)
{
int data[30];//stored result of crc bits
long data2[30];//stored result  in terms of the position of bit 2^n

  
 //  byte hmar[2];
 // hmar[0]=0xff;
 // hmar[1]=0x80; 
// Serial . write (hmar,2); // send the corresponding angle 
 
char buffer[1000];
//sprintf(buffer,"%0ld",1099511627775/10000);
 // Serial.print(16777216);
//  Serial.flush();
//  delay (1000);

   //c=205;
   //c=16383;

  int n=13;
  int i=0;
  while(i<30 )//add padding zeros to the 8 bit data to form the data frame of 30 bits
   {
    if (i<=13)
    {
 boolean b= bitRead(c,n);
 data[i]=b;
  n--;
    }
    else if (i>13)
    {
      data[i]=0; 
    }  
    i++;
   }    
i =0; 
while (i<=29)// to calculate the crc value by using crc-16modem polynomial p(x)=x^16+x^12+x^5+1
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
for (int i=0;i<=29;i++)//To convert the crc value from binary to decimal
 {
   data2[i]=data[t];
   data2[i]<<=i;  
   td+=data2[i];
  t--;
  }
//Serial.println("The crc values:");
//Serial.println(td,DEC);
//Serial.println("The crc calculation is finished");
long dataa =c;
long crc = td;
dataa<<=16;
td=td+dataa;//8bit data+16bit crc
//Serial.println("The txdata values:");
//for (int l=0;l<5;l++)
//{
// for (int h=0;h<5;h++)
// {
 Serial.print("i");            
 Serial.print(td); 
 Serial.print("f");  
 Serial.flush(); 
 //delay(10);  
 //}
//}
lcd.begin(16, 2);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("CRC=");
lcd.print(crc,DEC);
//lcd.print(" data:");
//lcd.print(data>>16,DEC);
lcd.setCursor(0,1);
lcd.print("TD=");
lcd.print(td,DEC);
}
