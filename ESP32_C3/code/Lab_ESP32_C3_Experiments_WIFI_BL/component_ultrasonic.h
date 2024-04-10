
/*   Ultrasonic
*/

#include <TM1637Display.h>
#include "component_motor.h"

#define CLK 2
#define DIO 7

TM1637Display display(CLK, DIO);

int trigPin = 5;  // Trigger
int echoPin = 4;  // Echo
long duration, distance;

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

  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  // Convert the time into a distance, cm
  distance = (duration / 2) / 29.1;  // Divide by 29.1 or multiply by 0.0343

  if (distance < 20) {
    int cur_cmd = DEV_STOP;
    motor_action(cur_cmd);
  }

  Serial.print(distance);
  Serial.println(F("cm"));
   display.showNumberDec(distance, false);
}

