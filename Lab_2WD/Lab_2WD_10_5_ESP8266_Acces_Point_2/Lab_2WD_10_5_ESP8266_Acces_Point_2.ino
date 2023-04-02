#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#ifndef APSSID
#define APSSID "ESP8266-WIFI"   //SSID
#define APPSK  "12345678" //Password
#endif

/* Set these to your desired credentials. */
const char *ssid = APSSID;
const char *password = APPSK;

IPAddress ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);

String  index_html(){
return  String("")+"<html>"+
"<head>"+
"<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"+
"<style>"+
"html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}"+
".button { background-color: #195B6A; border: none; color: white; padding: 3px 10px;"+
"width:150px; height: 30px;text-decoration: none; font-size: 18px; margin: 2px; cursor: pointer;}"+
"</style>"+
"</head>"+
"<title>Small Car</title>"+
"<body>"+
"<h1 align=center>Small Car</h1>"+
"<p><a href=\"/MOTOR=GO\"><button class=\"button\">Go</button></a></p>"+
"<p><a href=\"/MOTOR=STOP\"><button class=\"button\">STOP</button></a></p>"+
"<p><a href=\"/MOTOR=BACK\"><button class=\"button\">BACK</button></a></p>"+
"<p><a href=\"/MOTOR=LEFT\"><button class=\"button\">Turn Left</button></a></p>"+
"<p><a href=\"/MOTOR=RIGHT\"><button class=\"button\">Turn Right</button></a></p>"+
"<p><a href=\"/MOTOR=UP\"><button class=\"button\">Speed Up</button></a></p>"+
"<p><a href=\"/MOTOR=DOWN\"><button class=\"button\">Speed Down</button></a></p>"+
"<p>"+
"    <span>Distance</span>"+ 
"    <span id=\"distance\">%DISTANCE%</span>"+
"    <sup >cm</sup>"+
"</p>"+
"</body>"+
"</html>";
}

void handleRoot() {
  server.send(200, "text/html", index_html());
}

void handleMotor_GO() {
    Serial.println("G");
    server.send(200, "text/html", index_html());
}

void handleMotor_STOP() {
    Serial.println("S");
    server.send(200, "text/html", index_html());
}

void handleMotor_BACK() {
    Serial.println("S");
    server.send(200, "text/html", index_html());
}

void handleMotor_LEFT() {
    Serial.println("L");
    server.send(200, "text/html", index_html());
}

void handleMotor_RIGHT() {
    Serial.println("L");
    server.send(200, "text/html", index_html());
}

void handleMotor_UP() {
    Serial.println("U");
    server.send(200, "text/html", index_html());
}

void handle_received_data() {
    float distance=101.1;
    float left_speed=134.2;
    float right_speed=142.1;
    
    String json = "{";
    json += "\"distance\":"+String(distance);
    json += ", \"left_speed\":"+String(left_speed);
    json += ", \"right_speed\":"+String(right_speed);
    json += "}";
    server.send(200, "text/json", json);
}

void handleMotor_DOWN() {
    Serial.println("D");
}

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.print("Configuring access point...");

  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(ip, gateway, subnet);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.on("/MOTOR=GO",  handleMotor_GO);
  server.on("/MOTOR=STOP", handleMotor_STOP);
  server.on("/MOTOR=BACK", handleMotor_BACK);
  server.on("/MOTOR=LEFT", handleMotor_LEFT);
  server.on("/MOTOR=RIGHT",handleMotor_RIGHT);
  server.on("/MOTOR=UP", handleMotor_UP);
  server.on("/MOTOR=DOWN", handleMotor_DOWN);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  //handle_received_data();
}
