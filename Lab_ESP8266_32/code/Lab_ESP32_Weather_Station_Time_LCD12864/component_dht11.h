
#ifndef TH_H
#define TH_H

#include "DHT.h"
#include <Wire.h>
#include "component_lcd12864.h"

#define DHTPIN 15
#define DHTTYPE DHT11

float Humidity;
float Temperature;

DHT dht(DHTPIN, DHTTYPE);

long previousMillis_dht11;
const int interval_dht11 = 2000;

void setup_dht11() {
  dht.begin();
  previousMillis_dht11 = 0;
}

void dht11_on() {
  Humidity = dht.readHumidity() + 15.0;
  Temperature = dht.readTemperature();

  Serial.print(F("Humidity: "));
  Serial.print(Humidity);
  Serial.print(F("%  Temperature: "));
  Serial.print(Temperature);
  Serial.println(F("°C "));

  // Check if any reads failed and exit early (to try again).
  if (isnan(Humidity) || isnan(Temperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
}

void loop_dht11() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis_dht11 >= interval_dht11) {
    previousMillis_dht11 = currentMillis;  // Remember the time
    dht11_on();
    char strTemperature[4];
    char strhumidity[4];
    dtostrf(Temperature, 4, 2, strTemperature);                    // Converts a floating-point number to a string
    LCDA.DisplayString(1, 4, (unsigned char *)strTemperature, 2);  // Display humidity data
    dtostrf(Humidity, 4, 2, strhumidity);                          // Converts a floating-point number to a string
    LCDA.DisplayString(1, 6, (unsigned char *)strhumidity, 2);     // Display humidity data
  };
}
#endif /* TH_H */