#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "ArduinoJson.h"
#include "component_dht11.h"

//高德 - lives
String weatherURL = "https://restapi.amap.com/v3/weather/weatherInfo?key=d4aa79aeab835f56274c27742bb731cc&city=320100&extensions=base";
StaticJsonDocument<4096> doc;
HTTPClient http;

long previousMillis_weather;
const int interval_weather = 6000;


void getWeatherData() {
  // Serial.println(weatherURL);   // URL
  http.begin(weatherURL);     // HTTP begin
  int httpCode = http.GET();  // Make the request
  if (httpCode > 0) {
    //Serial.printf("HTTP Get Code: %d\r\n", httpCode);
    String weatherinfo = http.getString();  // get the weather info
    //Serial.print(weatherinfo);

    // Parse JSON
    DeserializationError err = deserializeJson(doc, weatherinfo);
    if (err == DeserializationError::Ok) {
      // Extract weather information
      String weather = doc["lives"][0]["weather"];
      int temperature = doc["lives"][0]["temperature"];
      int humidity = doc["lives"][0]["humidity"];
      String winddirection = doc["lives"][0]["winddirection"];
      String windpower = doc["lives"][0]["windpower"];
      // Print weather information
      Serial.printf("weather: %s \r\n", weather);
      Serial.printf("temperature: %d \r\n", temperature);
      Serial.printf("humidity: %d \r\n", humidity);
      Serial.printf("wind direction: %s \r\n", winddirection);
      Serial.printf("wind power: %s \r\n", windpower);
      Serial.printf("\r\n");
    } else {
      Serial.printf("Deserializion error: %s\n", err.f_str());
    }
  } else {
    Serial.printf("HTTP request failed with error code %d\n", httpCode);
  }
  http.end();  // Close connection
}

void WiFi_Connect() {
  const char *ssid = "TP-LINK_3DB3";     // type your ssid
  const char *password = "chengmaohua";  // type your password
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {  // 这里是阻塞程序，直到连接成功
    delay(300);
    Serial.print(".");
  }
}

void setup() {
  Serial.begin(115200);
  delay(100);
  Serial.print("Connecting.. ");

  WiFi_Connect();

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  previousMillis_weather = 0;

  setup_dht11();
  delay(2000);
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis_weather >= interval_weather) {
    previousMillis_weather = currentMillis;  // Remember the time
    getWeatherData();
  };
  loop_dht11();
}