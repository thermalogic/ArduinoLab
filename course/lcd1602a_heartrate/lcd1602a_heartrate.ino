/*
      2. Arduino Examples:LiquidCrystal LCD1602A

*/



#define USE_ARDUINO_INTERRUPTS true  // Set-up low-level interrupts for most acurate BPM math
#include <PulseSensorPlayground.h>   // Includes the PulseSensorPlayground Library

const int PulseWire = 0;  // 'S' Signal pin connected to A0
const int LED13 = 13;     // The on-board Arduino LED
int Threshold = 550;      // Determine which Signal to "count as a beat" and which to ignore

PulseSensorPlayground pulseSensor;  // Creates an object

// include the library code:
#include <LiquidCrystal.h>
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.begin(9600);

  // Configure the PulseSensor object, by assigning our variables to it
  pulseSensor.analogInput(PulseWire);
  pulseSensor.blinkOnPulse(LED13);  // Blink on-board LED with heartbeat
  pulseSensor.setThreshold(Threshold);

  // Double-check the "pulseSensor" object was created and began seeing a signal
  if (pulseSensor.begin()) {
    Serial.println("PulseSensor object created!");
  }
  lcd.begin(16, 2);
  lcd.print("Pulse Sensor");
  lcd.setCursor(0, 1);
  lcd.print(" BPM: ");
  delay(2000);
}

void loop() {
  int myBPM = pulseSensor.getBeatsPerMinute();     // Calculates BPM
  if (pulseSensor.sawStartOfBeat()) {              // Constantly test to see if a beat happened
    Serial.println("A HeartBeat Happened ! ");     // If true, print a message
    Serial.print("BPM: ");
    Serial.println(myBPM);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Pulse Sensor ");
    lcd.setCursor(0, 1);
    lcd.print(" BPM: ");
    lcd.print(myBPM);  // Print the BPM value
  }   
  delay(20);
}
