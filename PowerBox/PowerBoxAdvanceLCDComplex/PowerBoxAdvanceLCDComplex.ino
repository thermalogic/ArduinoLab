#include "TimerOne.h"
#include "Messenger.h"
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Messenger message = Messenger(); 

int Relay=8; //设定控制Relay的数字IO脚
int relayonoff;

float scaler5;
float Vref=5.0;
float rate;
float VVin,VVout,IVin,IVout;
float sqVVin,sumVVin,sqVVout,sumVVout;
float sqIVin,sumIVin,sqIVout,sumIVout;
//double VVinrms,VVoutrms,IVinrms,IVoutrms;
float sampleV,sqV,sumV,Vrms;
float sampleI,sqI,sumI,Irms;

float rPower,aPower,powerFactor,kWh;
float instP,sumP;

int SamplesInterval=1000;
int numberOfSampled=0;
int numberOfSamples=1000;
int numberOfAnaed=0;
int numberOfAna=1; //

void setup() {
    Serial.begin(9600);
    pinMode(Relay,OUTPUT);//设定数字IO口的模式，OUTPUT 为输出
    digitalWrite(Relay,HIGH); //设定PIN8脚为HIGH = 5V左右 继电器ON
    relayonoff=1;
 
    lcd.begin(16, 2);
    lcd.print("Welcome to NSFZ!");
    lcd.setCursor(1,1);    
    lcd.print("- Cheng Tianshi");
    delay(2000);
    //void initialize(long microseconds=1000000);
     Timer1.initialize(SamplesInterval); //
     Timer1.attachInterrupt(powervalue);
     message.attach(messageCompleted);
     
     scaler5=5.0/1023.0;
     rate=0.512/Vref;
 }

void loop()
{
   while ( Serial.available( ) ) message.process(Serial.read( ) );
}

void powervalue()
{
 if (numberOfSampled==0)
 { 
    sumV=0; 
    sampleV=0;
    sumVVin=0; 
    sumVVout=0;
 
    sumI=0; 
    sampleI=0;
    sumIVin=0;
    sumIVout=0;
    sumP=0; 
  }
  if (numberOfSampled<numberOfSamples)
  {
     IVout=analogRead(A0);
     VVout=analogRead(A1);
    
     VVout =scaler5*VVout; //    0-5v: 0-1023
     VVin=rate*(VVout-Vref/2) ; //Eq 3
     sampleV=-1931.111*VVin;
     sqV=sampleV*sampleV;
     sumV+=sqV;
     
     sqVVin=VVin*VVin;
     sumVVin+=sqVVin;
     
     sqVVout=VVout*VVout;
     sumVVout+=sqVVout;
     
     IVout = scaler5 *IVout; //    0-5v: 0-1023
     IVin=rate*(IVout-Vref/2) ; //Eq 3
     sampleI=5.0*IVin;
     sqI=sampleI*sampleI;
     sumI+=sqI;
     
     sqIVin=IVin*IVin;
     sumIVin+=sqIVin;
     
     sqIVout=IVout*IVout;
     sumIVout+=sqIVout;
 
     instP=sampleV*sampleI;
     sumP+=instP;
      numberOfSampled++;
   }
   else
   {
       Vrms=sqrt(sumV/numberOfSamples)-3.0;
       Irms=sqrt(sumI/numberOfSamples)-0.01;
       rPower=sumP/numberOfSamples;
       aPower=Vrms*Irms;
       powerFactor=rPower/aPower;
       kWh+=rPower/3600000.0; 
       numberOfSampled=0;;

    relayonoffbyVI();  
   
   if (numberOfAnaed>=numberOfAna)
   {  
       ProtocolMessage();
       lcddisp();
       numberOfAnaed=0;
   }
   else 
   {
      numberOfAnaed++;
   }
  }
}

void relayonoffbyVI()
{
  if((relayonoff==1)&&((Vrms>300)||(Irms>3)))
   {
      digitalWrite(Relay,LOW);
      relayonoff=0;
   };
}

void lcddisp()
{ 
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print(Vrms,0); 
   lcd.print("v");
   lcd.print(Irms,2); 
   lcd.print("a "); 
   lcd.print(rPower,1); 
   lcd.print("W");
  //------------------------------------------------
   lcd.setCursor(0, 1);
   lcd.print(powerFactor,2); 
   lcd.print(" "); 
   lcd.print(kWh,1);
   lcd.print("kWh");
   if (relayonoff==1)  lcd.print(" ON");
   if (relayonoff==0)  lcd.print("OFF");
 }

 void ProtocolMessage()
 {
       Serial.print(" VRMS "); 
       Serial.print(Vrms,4);
       Serial.print(" IRMS "); 
       Serial.print(Irms,4);
 
       Serial.print(" V "); 
       Serial.print(sampleV,4);
       Serial.print(" I "); 
       Serial.print(sampleI,4);

       Serial.print(" RP ");     
       Serial.print(rPower,4); 
       Serial.print(" AP "); 
       Serial.print(aPower,4); 
       Serial.print(" PF "); 
       Serial.print(powerFactor,3);
       Serial.print(" KWH "); 
       Serial.println(kWh,5);
 }
 

void messageCompleted() 
{
  while ( message.available())
  {
         
    if (message.checkString("on")) {
      if (relayonoff==0) {
          digitalWrite(Relay,HIGH);
          relayonoff=1;
       }
    }
   else
    if ( message.checkString("off"))
      {
        if (relayonoff==1) 
         {
          digitalWrite(Relay,LOW);
          relayonoff=0;
         } 
    }
  }
}
