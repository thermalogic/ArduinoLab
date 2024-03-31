/*
   Point your web browser to http://192.168.4.1/
*/

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <ArduinoJson.h>

#include "components.h"


// Set these to your desired credentials.
const char *ssid = "ESP32";
const char *password = "12345678";

WebServer server(80);

String json;
bool data_ready = false;

const char webpage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<style>
   html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}
   .button { background-color: #195B6A; border: none; color: white; padding: 3px 10px;
            width:150px; height: 30px;text-decoration: none; font-size: 18px; margin: 2px; cursor: pointer;}
</style>
</head>
<title>Small Car</title>
<body>
<h1 align=center>Small Car</h1>
<p><button class="button" onclick="send('Go')">Go</button></p>
<p><button class="button" onclick="send('Stop')">STOP</button></p>
<p><button class="button" onclick="send('Back')">BACK</button></p>
<p><button class="button" onclick="send('Left')">Turn Left</button></p>
<p><button class="button" onclick="send('Right')">Turn Right</button></p>
<p><button class="button" onclick="send('UpSpeed')">Speed Up</button></p>
<p><button class="button" onclick="send('DownSpeed')">Speed Down</button></p>
<div><h2> 
  Distance(cm): <span id="distance_val">0</span><br>
  </h2>
  <h3>Left Speed:&nbsp<span id="left_speed_val">0</span>
      &nbspRight Speed:&nbsp<span id="right_speed_val">0</span><br>
  </h3>
  <h2> Motor State: <span id="state">NA</span> </h2>
</div>
<div>
  <h3>Temp:&nbsp<span id="temp_val">0</span>
      &nbspHumi:&nbsp<span id="humi_val">0</span><br>
  </h3>
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
      var dataobj=JSON.parse(this.responseText);
      document.getElementById("distance_val").innerHTML = dataobj.distance;
      document.getElementById("left_speed_val").innerHTML = dataobj.left_speed;
      document.getElementById("right_speed_val").innerHTML = dataobj.right_speed;
  
      document.getElementById("temp_val").innerHTML = dataobj.temp;
      document.getElementById("humi_val").innerHTML = dataobj.humi;
  
    }
  };
  xhttp.open("GET", "data_read", true);
  xhttp.send();
}
</script>
</body>
</html>
)=====";

void handleRoot() {
  String s = webpage;
  server.send(200, "text/html", s);
}

void handleMotor() {
  String motor_cmd = server.arg("state");
  Serial.println(motor_cmd);
  server.send(200, "text/plane", motor_cmd);

  webclient_cmd(motor_cmd);
}

void handleSensor() {
  if (data_ready) {
    server.send(200, "text/json", json);
  } else {
    server.send(503, "text/plane", "none data");
  }
}

void webclient_cmd(String motor_cmd) {
  if (motor_cmd.compareTo("Go") == 0) {
    cur_dev_cmd = DEV_GO;
  } else if (motor_cmd.compareTo("Back") == 0) {
    cur_dev_cmd = DEV_BACK;
  } else if (motor_cmd.compareTo("Left") == 0) {
    cur_dev_cmd = DEV_LEFT;
  } else if (motor_cmd.compareTo("Right") == 0) {
    cur_dev_cmd = DEV_RIGHT;
  } else if (motor_cmd.compareTo("Stop") == 0) {
    cur_dev_cmd = DEV_STOP;
  } else if (motor_cmd.compareTo("UpSpeed") == 0) {
    cur_dev_cmd = DEV_UP;
  }
  if (motor_cmd.compareTo("DownSpeed") == 0) {
    cur_dev_cmd = DEV_DOWN;
  };
  do_action();
}


void setup() {
  Serial.begin(115200);
  setup_hardware();

  Serial.println();
  Serial.println("Configuring access point...");

  // You can remove the password parameter if you want the AP to be open.
  // a valid password must have more than 7 characters
  if (!WiFi.softAP(ssid, password)) {
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

void loop() {
  loop_hardware();
  json = "{";
  json += "\"distance\":" + String(distance, 10);
  json += ", \"left_speed\":" + String(10.0, 10);
  json += ", \"right_speed\":" + String(20.0, 10);
 //
  json += ", \"temp\":" + String(Temperature, 10);
  json += ", \"humi\":" + String(Humidity, 10);
  json += "}";
  data_ready = true;
  server.handleClient();
  delay(2);  //allow the cpu to switch to other tasks
}
