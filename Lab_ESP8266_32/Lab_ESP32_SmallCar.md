# 基于ESP32的小车

TODO: 
* WIFI的WebServer下，设备中有并行工作，如：web服务，接受红外信号，目前是串行的，对响应时间要求不高可以，要求高的话，需改为并行
* 系统架构和逻辑都实现，但没有加入电机控制代码

## ESP32 

![](img/esp32_pinout.jpg)

## 没有WebServer的小车控制

 * Lab_ESP32_IRremote_led_ultrasonic_tm1657
```c
#define IR_RECEIVE_PIN 19

#define LED_LEFT_PIN 18
#define LED_RIGHT_PIN 5

int trigPin = 12;    // Trigger
int echoPin = 13;    // Echo

// Module connection pins (Digital Pins)
#define CLK 26
#define DIO 27
```
### 问题

* Arduino UNO的analogwrite和digitalwrite不能同时使用控制LED

## 有WebServer的小车控制

* Lab_ESP32_SmallCar.ino

其中， 修改`Lab_ESP32_IRremote_led_ultrasonic_tm1657.ino`为`hardwares.h`,不是比合并到一个源码中，减少代码大量的代码合并工作