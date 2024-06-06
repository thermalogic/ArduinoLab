/*
  TThe Tracked Vehicle  with ESP32 and BTN7919
  WIFI:
     ssid = "ESP32-Tank";
     password = "12345678";
     http://192.168.4.1/
*/

#include "components.h"
#include "communication_wifi.h"

void setup()
{
  Serial.begin(115200);
  setup_components();
  setup_wifi();
}

void loop()
{
  loop_wifi();
  loop_components();
  delay(5); // allow the cpu to switch to other tasks
}
