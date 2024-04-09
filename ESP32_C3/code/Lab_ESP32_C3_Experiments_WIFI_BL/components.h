
/* SmallCar: ESP32-C3
 */

#include "component_ir.h"
#include "component_motor.h"

String json;
bool data_ready = false;

void setup_components()
{
    setup_motor();
    setup_ir();    
}

void loop_components()
{
    loop_motor();
    loop_ir();
    json = "{";
    json += "\"distance\":" + String(distance, 10);
    json += "}";
    data_ready = true;
}
