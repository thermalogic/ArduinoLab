#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "ArduinoJson.h"

//高德
String weaherURL = "https://restapi.amap.com/v3/weather/weatherInfo?key=d4aa79aeab835f56274c27742bb731cc&city=320100&extensions=all";

// DynamicJsonDocument doc(1024);
StaticJsonDocument<4096> doc;

HTTPClient http;

void getWeatherData() {
  Serial.println(weaherURL);  // 打印URL
  http.begin(weaherURL);      // HTTP begin
  int httpCode = http.GET();  // Make the request

  if (httpCode > 0) {
    Serial.printf("HTTP Get Code: %d\r\n", httpCode);
    String weatherinfo = http.getString();  // Get the response payload
    // Parse JSON
    DeserializationError err = deserializeJson(doc, weatherinfo);
    if (err == DeserializationError::Ok) {
      // Extract weather information
      float temperature = doc["forecasts"]["casts"][0]["daytemp"];
      // Print weather information
      Serial.printf("reporttime: %s\n", doc["forecasts"]["reporttime"]);
      Serial.printf("Temperature: %f \r\n", temperature);
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
  Serial.begin(9600);  // open the serial port at 115200 bps;
  delay(100);
  Serial.print("Connecting.. ");

  WiFi_Connect();

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  delay(2000);
}

void loop() {
  getWeatherData();
  delay(2000);
}