
/*  
  Tank  with ESP32
    Ultrasonic
*/
#ifndef UC_H
#define UC_H

#include "component_btn7919.h"
#include <Arduino.h>

int trigPin = 18;  // Trigger
int echoPin = 19;  // Echo
long duration;
float distance=0.0;

void setup_ultrasonic() {
  // Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop_ultrasonic() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  if (duration != 0) {
    distance = (duration / 2) / 29.1;  // Divide by 29.1 or multiply by 0.0343
    if (distance < 20) {
      int cur_cmd = DEV_STOP;
      car_action(cur_cmd);
    }

    Serial.print(distance);
    Serial.println(F("cm"));
  }
}

#endif /* UC_H */