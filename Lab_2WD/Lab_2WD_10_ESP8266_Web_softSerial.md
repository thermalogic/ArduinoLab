# ESP8266

**问题** 

ESP8266可以有2种方式提供web server

* 连接到无线路由的机器，提供服务 Lab_2WD_10_5_ESP8266_web_softserial.ino 使用`WiFiServer` server(80); 

* 作为无线热点，提供服务 Lab_2WD_10_5_ESP8266_Acces_Point_2 使用`ESP8266WebServer` server(80);

2种方式各有所长

* 第一种方式，连接ESP8266的设备，还可以访问其他设备，但是，需要在共同无线路由的网络下，离开无线路由，就不能提供服务
* 第二种方式，不需要无线路由就可以服务，但是，连接设备，这个时间，不能通过WIFI使用其他网络服务
## 代码

ESP8266和Arduino 中间数据通信采用json格式


 * Lab_2WD_10_5_ESP8266_Acces_Point_3.ino 异步ajax
 * Lab_2WD_10_5_Arduino_74HC595_IR_Web_speed_ul
 

```c
   inString = "{";
  inString += "\"distance\":" + String(63.1);
  inString += ", \"left_speed\":" +  String(138.1);
  inString += ", \"right_speed\":" + String(141.2);
  inString += "}";
```
## 问题

作为无线热点时，使用`WiFiServer`，不能提供服务

`WiFiServer`和`ESP8266WebServer`库的差别很大

Pro Mini烧录程序失败，2中烧录模块都失败-板子选择错误Arduino UNO,因为Pro Mini

## TODO

1. 现在的是同步web,改为异步web更好：

 ESP8266 Asynchronous Web Server

* 参考 https://randomnerdtutorials.com/esp8266-dht11dht22-temperature-and-humidity-web-server-with-arduino-ide/

2. 现在是ESP8266连接到无线路由，也可以将ESP作为WIFI热点:we will use the ESP8266 as Access Point

* https://www.survivingwithandroid.com/esp8266-web-server/

* https://randomnerdtutorials.com/esp8266-nodemcu-access-point-ap-web-server/
