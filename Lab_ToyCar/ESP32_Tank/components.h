
/* 
   Tank  with ESP32: components
*/

#include "component_btn7919.h"
#include "component_ultrasonic.h"
#include "component_ssd1306.h"
#include "component_servo.h"
//#include "component_ir.h"


String json;
bool data_ready = false;

void setup_components() {
  setup_servo();
  setup_btn7919();
  setup_ultrasonic();
  setup_ssd1306();
  // setup_ir();   
}

void loop_components() {

  loop_ultrasonic();
  loop_ssd1306();
  //loop_ir();
  json = "{";
  json += "\"distance\":" + String(distance, 2);
  json += "}";
  data_ready = true;
}
