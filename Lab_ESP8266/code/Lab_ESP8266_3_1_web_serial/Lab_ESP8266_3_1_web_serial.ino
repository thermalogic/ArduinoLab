/*
5C-CF-7F-A5-5C-7D绑定192.168.0.100
*/

#include <ESP8266WiFi.h>

const char* ssid = "TP-LINK_3DB3";     //type your ssid
const char* password = "chengmaohua";  //type your password

WiFiServer server(80);  //Service Port

void setup() {
  Serial.begin(9600);
  delay(10);

  // Connect to WiFi network
  //Serial.println();
  //Serial.println();
  //Serial.print("Connecting to ");
  //Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.print(".");
  }
  
  // Start the server
  server.begin();
  //Serial.println("Server started");

  // Print the IP address
  //Serial.print("Use this URL to connect: ");
  //Serial.print("http://");
  //Serial.print(WiFi.localIP());
  //Serial.println("/");
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  // Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");  //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<title>Car Web Controler</title>");
  client.println("<h1 align=center><font color=00FF00><span>Car Web Controler Using Arduino and ESP8266</font></span></h1>");
  client.println("<br><br>");
  client.println("Click <a href=\"/MOTOR=GO\">Car Go</a><br>");
  client.println("Click <a href=\"/MOTOR=STOP\">Car STOP</a><br>");
  client.println("Click <a href=\"/MOTOR=BACK\">Car Back</a><br>");
  client.println("Click <a href=\"/MOTOR=LEFT\">Turn Left</a><br>");
  client.println("Click <a href=\"/MOTOR=RIGHT\">Turn Right</a><br>");
  client.println("</html>");

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  // Serial.println(request);
  client.flush();

  // Match the request
  if (request.indexOf("/MOTOR=GO") != -1) {
    Serial.println("G");
  }
  if (request.indexOf("/MOTOR=STOP") != -1) {
    Serial.println("S");
  }
 if (request.indexOf("/MOTOR=BACK") != -1) {
    Serial.println("B");
  }
  if (request.indexOf("/MOTOR=LEFT") != -1) {
    Serial.println("L");
  }
  if (request.indexOf("/MOTOR=RIGHT") != -1) {
    Serial.println("R");
  }
 
  client.flush();
  delay(1);  //只服务1秒
  //Serial.println("Client disconnected");
  // Serial.println("");
}
