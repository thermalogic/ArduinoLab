#include "DHT.h"
#include <Wire.h>

#define DHTPIN 13
#define DHTTYPE DHT11

float Humidity;
float Temperature;

DHT dht(DHTPIN, DHTTYPE);

long previousMillis_dht11;
const int interval_dht11 = 1000;

void setup_dht11()
{
  dht.begin();
  previousMillis_dht11 = 0;
}

void dht11_on()
{
  Humidity = dht.readHumidity();
  Temperature = dht.readTemperature();
  
  Serial.print(F("Humidity: "));
   Serial.print(Humidity);
   Serial.print(F("%  Temperature: "));
   Serial.print(Temperature);
   Serial.print(F("°C "));
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(Humidity) || isnan(Temperature))
  {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
}

void loop_dht11()
{ 
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis_dht11 >= interval_dht11)
  {
    previousMillis_dht11 = currentMillis; // Remember the time
    dht11_on();
  };
}
