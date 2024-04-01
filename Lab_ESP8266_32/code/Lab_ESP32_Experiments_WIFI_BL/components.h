
/* SmallCar: ESP32
 */

#include "component_dht11.h"
#include "component_ultrasonic.h"
#include "component_ir.h"
#include "component_dev.h"

String json;
bool data_ready = false;

void setup_components()
{
    setup_dev();
    setup_ir();
    setup_ultrasonic();
    setup_dht11();
}

void loop_components()
{
    loop_dev();
    loop_ir();
    loop_ultrasonic();
    loop_dht11();
    json = "{";
    json += "\"distance\":" + String(distance, 10);
    json += ", \"left_speed\":" + String(10.0, 10);
    json += ", \"right_speed\":" + String(20.0, 10);
    //
    json += ", \"temp\":" + String(Temperature, 10);
    json += ", \"humi\":" + String(Humidity, 10);
    json += "}";
    data_ready = true;
}
