/*
  DRV8833-Dual-Motor-Driver-Module
*/

#include "component_motor.h"

int cur_cmd = DEV_STOP;

void setup() {
    Serial.begin(115200);
   setup_motor();
   
    cur_cmd = DEV_GO; 
    motor_action(cur_cmd);
    delay(2000);

    cur_cmd = DEV_BACK; 
    motor_action(cur_cmd);
    delay(2000);
 
   cur_cmd = DEV_LEFT;
  motor_action(cur_cmd);
  delay(2000);
   cur_cmd = DEV_RIGHT;
   motor_action(cur_cmd);
   delay(2000);
 
    cur_cmd = DEV_STOP;
    motor_action(cur_cmd);
    motor_stop();
        
}
 
void loop() {
 
}
