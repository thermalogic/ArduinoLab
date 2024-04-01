#include "DHT.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 13
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2); 

float Humidity;
float Temperature;

long previousMillis_dht11;
const int interval_dht11 = 1000;

void setup_dht11()
{
  dht.begin();
  previousMillis_dht11 = 0;

  lcd.init();          
  lcd.backlight();     
  lcd.setCursor(0, 0); 
  lcd.print("ESP32 Demo");
  lcd.setCursor(0, 1); 
  lcd.print("       2024");
}

void dht11_on()
{
  Humidity = dht.readHumidity();
  Temperature = dht.readTemperature();
  // Check if any reads failed and exit early (to try again).
  if (isnan(Humidity) || isnan(Temperature))
  {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Serial.print(F("Humidity: "));
  // Serial.print(Humidity);
  // Serial.print(F("%  Temperature: "));
  // Serial.print(Temperature);
  // Serial.print(F("°C "));

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Humi %: ");
  lcd.print(Humidity);
  lcd.setCursor(0, 1);
  lcd.print("Temp C: ");
  lcd.print(Temperature); 
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
