# Serial Communication Between Arduino and ESP-01

* https://www.instructables.com/Serial-Communication-Between-Arduino-and-ESP-01/

## 功能

* ESP8266连接到本地无线路由，提供Web服务，将web指令通过串口发给Arduino UNO

* Arduino UNO从串口接收来自 ESP8266命令执行有关操作

## 代码烧录步骤

1. 烧录空代码到Arduino UNO
2. 烧录ESP8266程序: Lab_ESP8266_3_1_ESP_Web_Serial
3. 交换RX和TX连线

   ![](img/Arduino_ESP8266.jpg)

4. 烧录Arduino UNO程序: Lab_ESP8266_3_2_Arduino_Serial

## 问题

* 页面手机不能打开，简单的web_led的可以
* 服务会不响应，需要重新启动板子

`是建立了太大的字符串，一次传递，不是一段一段的传递`？