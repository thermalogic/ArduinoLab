
/*
  ESP32 Experimente:
      LED
      IR
      Ultrasonic
      TM1657
      DHT11
      1602A I2C
*/

#include "components.h"

void setup()
{
  Serial.begin(115200);
  setup_components();
  delay(2000);
}

void loop()
{
  loop_components();
  delay(100);
}
