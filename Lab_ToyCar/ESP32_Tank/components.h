
/* 
   Tank  with ESP32: components
*/

#include "component_btn7919.h"
#include "component_ultrasonic.h"
#include "component_ssd1306.h"
//#include "component_ir.h"
#include "component_servo.h"
#include "component_dht11.h"

String json;
bool data_ready = false;

void setup_components() {
  setup_servo();
  setup_btn7919();
//  setup_ultrasonic();
 // setup_ir();   
//  setup_ssd1306();
}

void loop_components() {

  //loop_ultrasonic();
  //loop_ir();
  //loop_ssd1306();
  json = "{";
  json += "\"distance\":" + String(distance, 10);
  json += "}";
  data_ready = true;
}
