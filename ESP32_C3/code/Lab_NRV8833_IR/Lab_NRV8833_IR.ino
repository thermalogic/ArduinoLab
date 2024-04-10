/*
  DRV8833-Dual-Motor-Driver-Module
*/

#include "component_motor.h"
#include "component_ir.h"

int cur_cmd = DEV_STOP;

void setup() {
    Serial.begin(115200);
   // setup_motor();
    setup_ir();
   
   /* cur_cmd = DEV_GO; 
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

 digitalWrite(LEFT_FORWARD, LOW);
  digitalWrite(LEFT_BACK, LOW);
  digitalWrite(RIGHT_FORWARD, LOW);
  digitalWrite(RIGHT_BACK, LOW);

    cur_cmd = DEV_STOP;
    motor_action(cur_cmd);
     motor_stop();
    delay(2000);*/
    
}
 
void loop() {
   loop_ir_cmd();  
}
