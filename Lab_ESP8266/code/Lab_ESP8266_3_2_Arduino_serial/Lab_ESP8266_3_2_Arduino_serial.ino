/*
Arduino serial

*/

#define LED_PIN 13
String go="G";
String stop="S";
String back="B";
String left="L";
String right="R";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
}

void loop(){
  String inString="";
  while (Serial.available()) {
    inString += char(Serial.read());
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