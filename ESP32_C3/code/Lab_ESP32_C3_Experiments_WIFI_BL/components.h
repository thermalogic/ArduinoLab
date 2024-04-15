
/* SmallCar: ESP32-C3
 */

#include "component_ir.h"
#include "component_drv8833.h"
#include "component_ultrasonic.h"

String json;
bool data_ready = false;

void setup_components()
{
    setup_drv8833();
    // setup_ir();    
    //  setup_ultrasonic();
}

void loop_components()
{
    loop_drv8833();
    // loop_ir();
    // loop_ultrasonic();
    json = "{";
    json += "\"distance\":" + String(distance, 10);
    json += "}";
    data_ready = true;
}
