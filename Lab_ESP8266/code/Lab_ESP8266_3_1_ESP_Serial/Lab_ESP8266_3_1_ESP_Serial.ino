/*
 * Created By: Viraj Hapaliya
 */

#include <ESP8266WiFi.h>

// IPAddress staticIP63_10(192,168,121,190);
// IPAddress gateway63_10(192,168,121,253);
// IPAddress subnet63_10(255,255,255,0);

int val1, val2, val3, val4;

const char *ssid = "TP-LINK_3DB3";    // type your ssid
const char *password = "chengmaohua"; // type your password

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

void setup()
{
  Serial.begin(9600);

  delay(10);

  // Serial.println(ssid);

  WiFi.begin(ssid, password);
  //    WiFi.config(staticIP63_10, gateway63_10, subnet63_10);

  while (WiFi.status() != WL_CONNECTED)
  {
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

void loop()
{
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client)
  {
    return;
  }

  // Wait until the client sends some data
  // Serial.println("new client");
  while (!client.available())
  {
    delay(1);
  }
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n";
  // s += (val)?"high":"low";
  s += "<title>Car Web Controler</title>";
  s += "<h1 align=center><font color=00FF00><span>Car Web Controler Using Arduino and ESP8266</font></span></h1>\r\n";
  s += "<p align=center>L1 <a href=\"?pin=ON1\"><button>ON</button></a>&nbsp:<a href=\"?pin=OFF1\"><button>OFF</button></a></p>\r\n";
  s += "<p align=center>L2 <a href=\"?pin=ON2\"><button>ON</button></a>&nbsp:<a href=\"?pin=OFF2\"><button>OFF</button></a></p>\r\n";
  s += "<p align=center>L3 <a href=\"?pin=ON3\"><button>ON</button></a>&nbsp:<a href=\"?pin=OFF3\"><button>OFF</button></a></p>\r\n";
  s += "<p align=center>L4 <a href=\"?pin=ON4\"><button>ON</button></a>&nbsp:<a href=\"?pin=OFF4\"><button>OFF</button></a></p>\r\n";
  s += "</html>\n";

  // Send the response to the client
  client.print(s);
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  // Serial.println(req);
  client.flush();

  // Match the request
  if (req.indexOf("?pin=ON1") != -1)
  {
    Serial.print("0"); // 0
  }
  else if (req.indexOf("?pin=OFF1") != -1)
  {
    Serial.print("1"); // 1
  }
  else if (req.indexOf("?pin=ON2") != -1)
  {
    Serial.print("2"); // 2
  }
  else if (req.indexOf("?pin=OFF2") != -1)
  {
    Serial.print("3"); // 3
  }
  else if (req.indexOf("?pin=ON3") != -1)
  {
    Serial.println("4"); // 4
  }
  else if (req.indexOf("?pin=OFF3") != -1)
  {
    Serial.println("5"); // 5
  }
  else if (req.indexOf("?pin=ON4") != -1)
  {
    Serial.println("6"); // 6
  }
  else if (req.indexOf("?pin=OFF4") != -1)
  {
    Serial.println("7"); // 7
  }
  else
  {
    // Serial.println("invalid request");
    client.stop();
    return;
  }
  client.flush();

  delay(1);
}
