/*
 car web controller
*/

#include <ESP8266WiFi.h>

const char *ssid = "TP-LINK_3DB3";     // type your ssid
const char *password = "chengmaohua";  // type your password

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

void setup() {
  Serial.begin(9600);

  delay(10);

  // Serial.println(ssid);

  WiFi.begin(ssid, password);
  //    WiFi.config(staticIP63_10, gateway63_10, subnet63_10);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Serial.println("");
  // Serial.println("WiFi connected");

  // Start the server
  server.begin();
  // Serial.println("Server started");

  // Print the IP address
  // Serial.println(WiFi.localIP());
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

  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n";
  s += "<title>Car Web Controler</title>";
  s += "<h1 align=center><font color=00FF00><span>Car Web Controler Using Arduino and ESP8266</font></span></h1>\r\n";
  s += "<p align=center> <a href=\"?pin=GO\"><button>GO</button></a></p>\r\n";
  s += "<p align=center> <a href=\"?pin=BACK\"><button>BACK</button></a></p>\r\n";
  s += "<p align=center> <a href=\"?pin=LEFT\"><button>Turn Left</button></a></p>\r\n";
  s += "<p align=center> <a href=\"?pin=RIGHT\"><button>Turn Right</button></a></p>\r\n";
  s += "<p align=center> <a href=\"?pin=STOP\"><button>Stop</button></a></p>\r\n";
  s += "</html>\n";

  // Send the response to the client
  client.print(s);
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  // Serial.println(req);
  client.flush();

  // Match the request
  if (req.indexOf("?pin=GO") != -1) {
    Serial.print("G");
  } else if (req.indexOf("?pin=BACK") != -1) {
    Serial.print("B");
  } else if (req.indexOf("?pin=LEFT") != -1) {
    Serial.print("L");
  } else if (req.indexOf("?pin=RIGHT") != -1) {
    Serial.println("R");
  } else if (req.indexOf("?pin=STOP") != -1) {
    Serial.println("S");
  } else {
    // Serial.println("invalid request");
    client.stop();
    return;
  }
  client.flush();

  delay(1);
}
