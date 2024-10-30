#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <ESP32Time.h>
#include "ArduinoJson.h"
#include "component_dht11.h"
#include "component_lcd12864.h"

WiFiUDP ntpUDP;
// NTPClient(UDP& udp, const char* poolServerName, long timeOffset, unsigned long updateInterval);
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 28800, 60000);
unsigned long epochTime;
ESP32Time rtc(0);

// 高德 - lives
String weatherURL = "https://restapi.amap.com/v3/weather/weatherInfo?key=d4aa79aeab835f56274c27742bb731cc&city=320100&extensions=base";
StaticJsonDocument<4096> doc;
HTTPClient http;
long previousMillis_weather;
const int interval_weather = 60000;

void getWeatherData() {
  // Serial.println(weatherURL);   // URL
  http.begin(weatherURL);     // HTTP begin
  int httpCode = http.GET();  // Make the request
  if (httpCode > 0) {
    // Serial.printf("HTTP Get Code: %d\r\n", httpCode);
    String weatherinfo = http.getString();  // get the weather info
    // Serial.print(weatherinfo);

    // Parse JSON
    DeserializationError err = deserializeJson(doc, weatherinfo);
    if (err == DeserializationError::Ok) {
      // Extract weather information
      //String weather = doc["lives"][0]["weather"];
      int temperature = doc["lives"][0]["temperature"];
      int humidity = doc["lives"][0]["humidity"];
      //String winddirection = doc["lives"][0]["winddirection"];
      //String windpower = doc["lives"][0]["windpower"];
      //String reporttime = doc["lives"][0]["reporttime"];
      // Print weather information
      //Serial.printf("weather: %s \r\n", weather);
      Serial.printf("temperature: %d \r\n", temperature);
      Serial.printf("humidity: %d \r\n", humidity);
      //Serial.printf("wind direction: %s \r\n", winddirection);
      //Serial.printf("wind power: %s \r\n", windpower);
      //Serial.printf("reporttime: %s \r\n", reporttime);
      Serial.printf("\r\n");
      // LCD Display
      // LCDA.DisplayString(0,2, (unsigned char *)reporttime.c_str(), 10);
      char strTemperature[5];
      char strhumidity[5];
      dtostrf(temperature, 5, 2, strTemperature);
      LCDA.DisplayString(2, 4, (unsigned char *)strTemperature, 2);  // Display humidity data
      dtostrf(humidity, 5, 2, strhumidity);                          // Converts a floating-point number to a string
      LCDA.DisplayString(2, 6, (unsigned char *)strhumidity, 2);     // Display humidity data
    } else {
      Serial.printf("Deserializion error: %s\n", err.f_str());
    }
  } else {
    Serial.printf("HTTP request failed with error code %d\n", httpCode);
  }
  http.end();  // Close connection
}

void loop_ntp_time() {
  timeClient.update();
  epochTime = timeClient.getEpochTime();
  rtc.setTime(epochTime);
  LCDA.DisplayString(0, 1, (unsigned char *)rtc.getTime(" %Y-%m-%d").c_str(), 11);
  LCDA.DisplayString(3, 2, (unsigned char *)rtc.getTime("%H:%M:%S").c_str(), 8);
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

  timeClient.begin();
  setup_lcd12864();
  setup_dht11();

  loop_ntp_time();
  dht11_on();
  previousMillis_weather = 0;
  getWeatherData();
}

void loop() {
  loop_ntp_time();
  loop_dht11();

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis_weather >= interval_weather) {
    previousMillis_weather = currentMillis;  // Remember the time
    getWeatherData();
  };
  delay(500);
}