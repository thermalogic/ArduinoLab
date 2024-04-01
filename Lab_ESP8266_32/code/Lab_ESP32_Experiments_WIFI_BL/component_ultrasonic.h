
/*   Ultrasonic
     TM1657
*/

#include <TM1637Display.h>
#include "component_dev.h"

#define CLK 26
#define DIO 27

int trigPin = 12;  // Trigger
int echoPin = 13;  // Echo
long duration, distance;

TM1637Display display(CLK, DIO);

void setup_ultrasonic() {
  // Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };
  display.setBrightness(0x0f);
  // All segments on
  display.setSegments(data);
  }

void loop_ultrasonic() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  // Convert the time into a distance, cm
  distance = (duration / 2) / 29.1;  // Divide by 29.1 or multiply by 0.0343

  if (distance < 20) {
    cur_cmd = DEV_STOP;
    do_action();
  }

  //Serial.print(distance);
  //Serial.println(F("cm"));
  display.showNumberDec(distance, false);

} 
