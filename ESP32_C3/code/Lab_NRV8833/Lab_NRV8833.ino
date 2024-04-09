/*
  DRV8833-Dual-Motor-Driver-Module
*/

#include "component_motor.h"

int cur_cmd = DEV_STOP;

void setup() {
  setup_motor();

digitalWrite(LEFT_FORWARD, HIGH);
digitalWrite(LEFT_BACK, LOW);
  delay(2000);
  
 digitalWrite(LEFT_FORWARD,LOW);
digitalWrite(LEFT_BACK, HIGH);
  
  delay(2000);

 digitalWrite(LEFT_FORWARD,LOW);
 digitalWrite(LEFT_BACK, LOW);
  
  
  //digitalWrite(RIGHT_FORWARD, HIGH);
 // digitalWrite(RIGHT_BACK, LOW);
  delay(2000);
  
  //digitalWrite(RIGHT_FORWARD,LOW);
 // digitalWrite(RIGHT_BACK, HIGH);
  
 // delay(2000);

  //digitalWrite(RIGHT_FORWARD,LOW);
 // digitalWrite(RIGHT_BACK, LOW);
  

  // cur_cmd = DEV_GO; // right
  // motor_action(cur_cmd);
   //delay(2000);
   //cur_cmd = DEV_BACK; // go
  // motor_action(cur_cmd);
  // delay(2000);
  // cur_cmd = DEV_STOP;
  // motor_action(cur_cmd);
  // delay(2000);
  // cur_cmd = DEV_LEFT;
  // motor_action(cur_cmd);
  // delay(2000);
  // cur_cmd = DEV_RIGHT;
  // motor_action(cur_cmd);
  
}
 
void loop() {
  
     
}
