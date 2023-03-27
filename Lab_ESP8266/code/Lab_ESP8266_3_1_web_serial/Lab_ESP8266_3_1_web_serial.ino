/*
5C-CF-7F-A5-5C-7D绑定192.168.0.100
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

  if(!client){
    return; 
  } ;  
  delay(50); // 
  if(client.available()) 
  {
    // Return the response
    client.println(F("HTTP/1.1 200 OK"));
    client.println(F("Content-Type: text/html"));
    client.println(F("")); //  do not forget this one
    client.println(F("<!DOCTYPE HTML>"));
    client.println(F("<html>"));
    client.println(F("<title>Car Web Controler</title>"));
    client.println(F("<h1 align=center>Car with ESP8266</h1>"));
    client.println(F("<br><br>"));
    client.println(F("<a href=\"/MOTOR=GO\">Go</a><br>"));
    client.println(F("<a href=\"/MOTOR=STOP\">STOP</a><br>"));
    client.println(F("<a href=\"/MOTOR=BACK\">Back</a><br>"));
    client.println(F("<a href=\"/MOTOR=LEFT\">Turn Left</a><br>"));
    client.println(F("<a href=\"/MOTOR=RIGHT\">Turn Right</a><br>"));
    client.println(F("</html>"));
    
    String request = client.readStringUntil('\r');
    client.flush();

    // Match the request
    if (request.indexOf("/MOTOR=GO") != -1)
    {
      Serial.println("G");
    }
    if (request.indexOf("/MOTOR=STOP") != -1)
    {
      Serial.println("S");
    }
    if (request.indexOf("/MOTOR=BACK") != -1)
    {
      Serial.println("B");
    }
    if (request.indexOf("/MOTOR=LEFT") != -1)
    {
      Serial.println("L");
    }
    if (request.indexOf("/MOTOR=RIGHT") != -1)
    {
      Serial.println("R");
    }
   
    
    
  }
}
