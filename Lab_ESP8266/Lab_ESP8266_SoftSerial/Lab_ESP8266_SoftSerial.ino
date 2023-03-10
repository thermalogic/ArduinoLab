#include <SoftwareSerial.h>
SoftwareSerial mySerial(8, 9); // RX, TX
void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  delay(1000);
  Serial.println("Goodnight  moon2");
  mySerial.println("AT+GMR");
}
void loop() {
  while (mySerial.available()) {
    Serial.write(mySerial.read());
  }
}