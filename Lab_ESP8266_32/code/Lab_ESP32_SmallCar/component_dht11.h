#include "DHT.h"
#define DHTPIN 4  
#define DHTTYPE DHT11

float Humidity;
float Temperature;

DHT dht(DHTPIN, DHTTYPE);

void setup_dht11()
{

    dht.begin();

}

void loop_dht11() {
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  Humidity = dht.readHumidity();
  // Read temperature as Celsius (the default)
  Temperature  = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(Humidity) || isnan(Temperature) ) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
 
  Serial.print(F("Humidity: "));
  Serial.print(Humidity);
  Serial.print(F("%  Temperature: "));
  Serial.print(Temperature);
  Serial.print(F("°C "));
 }
