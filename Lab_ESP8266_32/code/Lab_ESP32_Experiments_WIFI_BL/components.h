
/* SmallCar: ESP32
 */

#include "component_dht11.h"
#include "component_ultrasonic.h"
#include "component_ir.h"
#include "component_dev.h"

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
}
