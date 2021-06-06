
int data[24];//stored result of crc bits
long data2[24];//stored result  in terms of the position of bit 2^n
int c;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.setTimeout(50);  
pinMode(13,OUTPUT);
digitalWrite(13,LOW);
}
void loop() {  
  c=205;
  int n=7;
  int i=0;
  while(i<24 )//add padding zeros to the 8 bit data to form the data frame of 24 bits
   {
    if (i<=7)
    {
 boolean b= bitRead(c,n);
 data[i]=b;
  n--;
    }
    else if (i>7)
    {
      data[i]=0; 
    }  
    i++;
   }    
i =0; 
while (i<=23)// to calculate the crc value by using crc-16modem polynomial p(x)=x^16+x^12+x^5+1
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
for (int i=0;i<=23;i++)//To convert the crc value from binary to decimal
 {
   data2[i]=data[t];
   data2[i]<<=i;  
   td+=data2[i];
  t--;
  }
Serial.println("The crc values:");
Serial.println(td,DEC);
Serial.println("The crc calculation is finished");

long data =c;
data<<=16;
td=td+data;
Serial.println("The txdata values:");
Serial.println(td,DEC);
Serial.println("The txdata calculation is finished");
}
