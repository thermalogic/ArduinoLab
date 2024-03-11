/*
Arduino serial

*/
#include <SoftwareSerial.h>

#define LED_PIN 9
String go="G";
String stop="S";
String back="B";
String left="L";
String right="R";

#define SS_RX 3
#define SS_TX 2

SoftwareSerial  mySerial(SS_RX,SS_TX);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  mySerial.begin(9600);

}

void loop(){
  String inString="";
  while (mySerial.available()) {
    inString += char(mySerial.read());
    Serial.print(inString);
  };
  if (inString==go){
     digitalWrite(LED_PIN, HIGH);
  };
  if (inString==stop){
     digitalWrite(LED_PIN, LOW);
  }
  if (inString==back){
     digitalWrite(LED_PIN, LOW);
  }
  if (inString==left){
     digitalWrite(LED_PIN, HIGH);
  }
  if (inString==right){
     digitalWrite(LED_PIN, LOW);
  }


}