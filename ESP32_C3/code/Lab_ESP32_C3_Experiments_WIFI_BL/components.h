
/* 
   MiniCar with ESP32-C3: components
*/

#include "component_drv8833.h"
#include "component_ultrasonic.h"
#include "component_ir.h"

String json;
bool data_ready = false;

void setup_components()
{
    setup_drv8833();
    setup_ultrasonic();
    setup_ir();    
}

void loop_components()
{
    loop_drv8833();
    loop_ultrasonic();
    loop_ir();
    json = "{";
    json += "\"distance\":" + String(distance, 10);
    json += "}";
    data_ready = true;
}
