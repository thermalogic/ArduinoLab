#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT11

float Humidity;
float Temperature;

DHT dht(DHTPIN, DHTTYPE);

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  //配置LCD地址及行列

long previousMillis_dht11;
const int interval_dht11 = 1000;

void setup_dht11() {

  dht.begin();

  lcd.init();           //初始化LCD
  lcd.backlight();      //打开背光
  lcd.setCursor(0, 0);  //设置显示位置
  lcd.print("ESP32 Demo");
  lcd.setCursor(0, 1);  //设置显示位置
  lcd.print(" Cheng Maohua: ");
}

void dht11_on() {
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  Humidity = dht.readHumidity();
  // Read temperature as Celsius (the default)
  Temperature = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(Humidity) || isnan(Temperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print(F("Humidity: "));
  Serial.print(Humidity);
  Serial.print(F("%  Temperature: "));
  Serial.print(Temperature);
  Serial.print(F("°C "));

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Humi %: ");
  lcd.print(Humidity);
  lcd.setCursor(0, 1);
  lcd.print("Temp C: ");
  lcd.print(Temperature);  // Print the BPM valu
}

void loop_dht11() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis_dht11 >= interval_dht11) {
    previousMillis_dht11 = currentMillis;  // Remember the time
    dht11_on();
  };
}
