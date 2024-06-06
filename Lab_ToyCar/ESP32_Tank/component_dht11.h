
#ifndef TH_H
#define TH_H

#include "DHT.h"

#define DHTPIN 13
#define DHTTYPE DHT11  // DHT 11

DHT dht(DHTPIN, DHTTYPE);
int h;
int t;


void setup_dht11() {
  dht.begin();
}

void loop_dht11() {
  
  h = dht.readHumidity();
  t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
}

#endif /* TH_H */