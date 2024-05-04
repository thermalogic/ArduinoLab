/*
  MiniCar with ESP32-C3
  WIFI:
     ssid = "ESP32-C3";
     password = "12345678";
     http://192.168.4.1/
  Bluetooth:
    ESP32-C3-BT-Slave
*/

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <WebServer.h>

#include "components.h"
#include "communication_wifi.h"
#include "communication_bluetooth.h"

void setup()
{
  Serial.begin(115200);
  setup_components();
  setup_wifi();
  setup_bluetooth();
}

void loop()
{
  loop_components();
  loop_wifi();
  loop_bluetooth();
  delay(2); // allow the cpu to switch to other tasks
}
