
/*  
  MiniCar with ESP32-C3:  Ultrasonic
*/
#ifndef UC_H
#define UC_H

#include "component_btn7919.h"
#include <Arduino.h>

int trigPin = 10; //5;  // Trigger
int echoPin = 6; //4;  // Echo
long duration;
float distance;
//long mem_distance[5];
//long sum_distance=0;
//int count=0; 

void setup_ultrasonic() {
  // Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //count=-1; 
 //for(int i=0; i<5; i++)
 //    mem_distance[i]=0;

}

void loop_ultrasonic() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  

  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

/*  if (count<=4)
  { 
    count++; 
    mem_distance[count] = (duration / 2) / 29.1;  // Divide by 29.1 or multiply by 0.0343
  }
  else
  {
    for(int i=0; i<=4; i++)
       mem_distance[i] = mem_distance[i+1];  // Divide by 29.1 or multiply by 0.0343
    mem_distance[count] = (duration / 2) / 29.1;  // Divide by 29.1 or multiply by 0.0343
  }
  
  sum_distance=0;
  for(int i=0; i<count; i++)
     sum_distance+=mem_distance[i];
  distance =sum_distance/count;
*/


 distance = (duration / 2) / 29.1;  // Divide by 29.1 or multiply by 0.0343
 
  if (distance < 20) {
    int cur_cmd = DEV_STOP;
    car_action(cur_cmd);
  }

  //Serial.print(distance);
 // Serial.println(F("cm"));
  }
#endif /* UC_H */