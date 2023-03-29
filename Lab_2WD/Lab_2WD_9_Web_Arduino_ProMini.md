#  红外和Web控制的小车

基于Serial Communication Between Arduino Pro Mini and ESP-01实现Web控制的小车

* Lab_2WD_9_Mini_Non_Ultrasonic_Web.ino

**TODO**

可以集成为`WIFI`控制小车，但需要减少LED,端口不够

## 功能

* Arduino Pro Mini和红外灯安装在一个小面包板上

* ESP8266提供web服务，并将信息通过串口发送给Arduino Pro Mini

* Arduino Pro Mini使用用`软串口`和ESP8266通信

Arduino端有多个串口时，需要使用`软串口`和ESP8266通信

**注意**：红外库使用板载的pin13作为反馈信号灯，所以，`软串口`不使用pin13 




