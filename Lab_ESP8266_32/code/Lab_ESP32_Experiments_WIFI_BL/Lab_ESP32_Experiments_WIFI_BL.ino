/*
  WIFI Access Point:
    ESP32 @ http://192.168.4.1/
  Bluetooth:
    ESP32-BT-Slave
*/

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <WebServer.h>

#include "components.h"
#include "communication_bluetooth.h"
#include "communication_wifi.h"

void setup()
{
  Serial.begin(115200);
  setup_components();
  setup_bluetooth();
  setup_wifi();
}

void loop()
{
  loop_components();
  loop_bluetooth();
  loop_wifi();
  delay(2); // allow the cpu to switch to other tasks
}
