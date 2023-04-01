/*
5C-CF-7F-A5-5C-7D绑定192.168.0.107
*/

#include <ESP8266WiFi.h>

const char *ssid = "TP-LINK_3DB3";    // type your ssid
const char *password = "chengmaohua"; // type your password
boolean haveClient = false;

WiFiServer server(80); // Service Port

void setup()
{
  Serial.begin(9600);
  delay(10);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }

  // Start the server
  server.begin();
}

void loop()
{
  // Check if a client has connected
  WiFiClient client = server.available();

  if (!client)
  {
    return;
  };
  delay(50); //
  if (client.available())
  {
    // Return the response
    client.println(F("HTTP/1.1 200 OK"));
    client.println(F("Content-Type: text/html"));
    client.println(F("")); //  do not forget this one
    client.println(F("<!DOCTYPE HTML>"));
    client.println(F("<html>"));
    client.println(F("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"));
    // CSS to style the on/off buttons 
    client.println(F("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}"));
    client.println(F(".button { background-color: #195B6A; border: none; color: white; padding: 3px 10px;"));
    client.println(F("width:150px; height: 30px;text-decoration: none; font-size: 18px; margin: 2px; cursor: pointer;}"));
    client.println(F("</style></head> "));
    client.println(F("<title>Small Car</title>")); 
    client.println(F("<body>"));
    client.println(F("<h1 align=center>Small Car</h1>"));
    client.println(F("<p><a href=\"/MOTOR=GO\"><button class=\"button\">Go</button></a></p>"));
    client.println(F("<p><a href=\"/MOTOR=STOP\"><button class=\"button\">STOP</button></a></p>"));
    client.println(F("<p><a href=\"/MOTOR=BACK\"><button class=\"button\">BACK</button></a></p>"));
    client.println(F("<p><a href=\"/MOTOR=LEFT\"><button class=\"button\">Turn Left</button></a></p>"));
    client.println(F("<p><a href=\"/MOTOR=RIGHT\"><button class=\"button\">Turn Right</button></a></p>"));
    client.println(F("<p><a href=\"/MOTOR=UP\"><button class=\"button\">Speed Up</button></a></p>"));
    client.println(F("<p><a href=\"/MOTOR=DOWN\"><button class=\"button\">Speed Down</button></a></p>"));
    client.println(F("</body></html>"));

    String request = client.readStringUntil('\r');
    client.flush();

    // Match the request
    if (request.indexOf("/MOTOR=GO") != -1) {
      Serial.println("G");
    } else if (request.indexOf("/MOTOR=STOP") != -1) {
      Serial.println("S");
    } else if (request.indexOf("/MOTOR=BACK") != -1) {
      Serial.println("B");
    } else if (request.indexOf("/MOTOR=LEFT") != -1) {
      Serial.println("L");
    } else if (request.indexOf("/MOTOR=RIGHT") != -1) {
      Serial.println("R");
    } else if (request.indexOf("/MOTOR=UP") != -1) {
      Serial.println("U");
    } else if (request.indexOf("/MOTOR=DOWN") != -1) {
      Serial.println("D");
    };
  }
}