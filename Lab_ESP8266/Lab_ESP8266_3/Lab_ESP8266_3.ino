#include <ESP8266WiFi.h>

// WiFi parameters
const char* ssid = "TP-LINK-3DB2";
const char* password = "chengmaohua";

void setup(void)
{
  // Start Serial
  Serial.begin(115200);
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Print the IP address
  Serial.println(WiFi.localIP());
}
       
void loop() {
}