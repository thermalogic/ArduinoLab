/*
      2. Arduino Examples: TM1637A

*/

#include <Arduino.h>
#include <TM1637Display.h>

// Module connection pins (Digital Pins)
#define CLK 2
#define DIO 3

// The amount of time (in milliseconds) between tests
#define TEST_DELAY   2000

const uint8_t SEG_DONE[] = {
	SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,           // d
	SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
	SEG_C | SEG_E | SEG_G,                           // n
	SEG_A | SEG_D | SEG_E | SEG_F | SEG_G            // E
	};


TM1637Display display(CLK, DIO);

#define USE_ARDUINO_INTERRUPTS true  // Set-up low-level interrupts for most acurate BPM math
#include <PulseSensorPlayground.h>   // Includes the PulseSensorPlayground Library

const int PulseWire = 0;  // 'S' Signal pin connected to A0
const int LED13 = 13;     // The on-board Arduino LED
int Threshold = 550;      // Determine which Signal to "count as a beat" and which to ignore

PulseSensorPlayground pulseSensor;  // Creates an object

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

  uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };
  display.setBrightness(0x0f);
  // All segments on
  display.setSegments(data);
  delay(500);
}

void loop() {
  int myBPM = pulseSensor.getBeatsPerMinute();     // Calculates BPM
  if (pulseSensor.sawStartOfBeat()) {              // Constantly test to see if a beat happened
    Serial.println("A HeartBeat Happened ! ");     // If true, print a message
    Serial.print("BPM: ");
    Serial.println(myBPM);
    display.showNumberDec(myBPM,false);
    delay(20);
  }
}
