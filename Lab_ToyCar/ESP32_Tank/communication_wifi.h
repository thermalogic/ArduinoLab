/*
  Tank  with ESP32: WIFI
     ssid = "ESP32-Tank";
     password = "12345678";
     http://192.168.4.1/
*/
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <WebServer.h>
#include "component_btn7919.h"
#include "component_servo.h"

// Set these to your desired credentials.
const char *ssid = "ESP32-Tank";
const char *password = "12345678";

WebServer server(80);

const char webpage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<style>
   html { font-family: sans-serif; display: inline-block; margin: 0px auto; text-align: center;}
   .button { background-color: #195B6A; border: none; color: white; padding: 3px 10px;
            width:150px; height: 30px;text-decoration: none; font-size: 18px; margin: 2px; cursor: pointer;}
</style>
</head>
<title>Tank</title>
<body>
<h1 align=center>Tank</h1>
<p><button class="button" onclick="send('G')">Go</button></p>
<p><button class="button" onclick="send('S')">STOP</button></p>
<p><button class="button" onclick="send('B')">BACK</button></p>
<p><button class="button" onclick="send('L')">Turn Left</button></p>
<p><button class="button" onclick="send('R')">Turn Right</button></p>
<p><button class="button" onclick="send('C')">Servo Clock</button></p>
<p><button class="button" onclick="send('A')">Servo AntiC</button></p>
<div><h2> 
  Distance(cm): <span id="distance">0</span><br>
  </h2>
  <h2>Car State: <span id="state">NA</span> </h2>
</div>
<script>
function send(motor_cmd) 
{
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("state").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "motor_set?state="+motor_cmd, true);
  xhttp.send();
}

setInterval(function() 
{
  getData();
}, 1000); 

function getData() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      var data=JSON.parse(this.responseText);
      document.getElementById("distance").innerHTML = data.distance;
    }
  };
  xhttp.open("GET", "data_read", true);
  xhttp.send();
}
</script>
</body>
</html>
)=====";

void webclient_cmd(String motor_cmd)
{
  int cur_cmd = DEV_STOP;
  if (motor_cmd.compareTo("G") == 0)
  {
    cur_cmd = DEV_GO;
  }
  else if (motor_cmd.compareTo("B") == 0)
  {
    cur_cmd = DEV_BACK;
  }
  else if (motor_cmd.compareTo("L") == 0)
  {
    cur_cmd = DEV_LEFT;
  }
  else if (motor_cmd.compareTo("R") == 0)
  {
    cur_cmd = DEV_RIGHT;
  }
  else if (motor_cmd.compareTo("S") == 0)
  {
    cur_cmd = DEV_STOP;
  }
  else if (motor_cmd.compareTo("C") == 0)
  {
    cur_cmd = DEV_STOP;
    car_action(cur_cmd);
    ultrasonic_servo_action( SERVO_CLOCKWISE);
  }
  else if (motor_cmd.compareTo("A") == 0)
  {
    cur_cmd = DEV_STOP;
    car_action(cur_cmd);
    ultrasonic_servo_action( SERVO_ANTI_CLOCKWISE);
  };
  car_action(cur_cmd);
}

void handleRoot()
{
  String s = webpage;
  server.send(200, "text/html", s);
}

void handleMotor()
{
  String motor_cmd = server.arg("state");

  Serial.println(motor_cmd);

  server.send(200, "text/plane", motor_cmd);
  webclient_cmd(motor_cmd);
}

void handleSensor()
{
  if (data_ready)
  {
    server.send(200, "text/json", json);
  }
  else
  {
    server.send(503, "text/plane", "none data");
  }
}

void setup_wifi()
{
  Serial.println();
  Serial.println("Configuring access point...");

  // You can remove the password parameter if you want the AP to be open.
  // a valid password must have more than 7 characters
  if (!WiFi.softAP(ssid, password))
  {
    log_e("Soft AP creation failed.");
    while (1)
      ;
  }

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  server.on("/", handleRoot);
  server.on("/motor_set", handleMotor);
  server.on("/data_read", handleSensor);
  server.begin();
  Serial.println("Server started");
}

void loop_wifi()
{
  server.handleClient();
}
