# ESP32综合实验

TODO: 

* WIFI的WebServer下，设备中有并行工作，如：web服务，接受红外信号，目前是串行的，对响应时间要求不高可以，要求高的话，需改为并行
* 系统架构和逻辑都实现，但没有加入电机控制代码
* 红外，蓝牙和WIFI多模式控制的代码执行- 后退时，LED开始闪烁几下后，一直亮

![](img/esp32_experiments.jpg)

## 代码

代码模块化组织。组件代码以头文件的形式存在，合成为一个总的应用。

不是将使用代码合并到一个文件源码中，减少代码大量的代码合并工作，模块化组织使得可维护性更好

### 红外，蓝牙和WIFI多模式控制

`Lab_ESP32_Experiments_WIFI_BL.ino`

* 元件组：components.h
* DHT11,LCD元件：component_dht11.h
* 蓝牙：communication_bluetooth.h

### 各种方案代码

* IRI控制：`Lab_ESP32_Experiment_IR.ino`,通过
 
* WIFI控制：`Lab_ESP32_Experiments_WIFI.ino`,通过

* 蓝牙控制：`Lab_ESP32_Experiments_bluetooth.ino`,通过

## 元件

* 红外
* LED
* 超声
* TM1637数码管
* 温湿度:DHT11
* 1602A I2C显示

## ESP32 

![](img/esp32_pinout.jpg)

## 元件连接

### components.h

 ```c
#define IR_RECEIVE_PIN 19

#define LED_LEFT_PIN 18
#define LED_RIGHT_PIN 5

int trigPin = 12;    // Trigger
int echoPin = 13;    // Echo

// TM1637 Module connection pins (Digital Pins)
#define CLK 26
#define DIO 27
```

### component_dht11.h

* DHT11

DHT11使用库： DHT library from Adafruit

```c
#define DHTPIN 4  
```
* 1602A I2C

I2C LCD	ESP32
GND -> GND
VCC -> VIN -  注意：用USB给ESP32供电时，可以从VIN取5V的电，ESP32的输出3.3V驱动1602A电压低，显示不清楚
SDA	-> GPIO 21
SCL	-> GPIO 22

## 问题

### 程序过大的问题的解决
 
WIFI和蓝牙的使用，其库都需要使用很多存储空间，其中，蓝牙更多

如果将WIFI和蓝牙合并：`Lab_ESP32_Experiments_WIFI_BL.ino`，编译后代码大，默认的Partition Scheme下超15%，无法编译通过

改变Partition Scheme,选择Huge APP(3MB)

* Sketch uses 1523121 bytes (48%) of program storage space. Maximum is 3145728 byte

### 代解决问题

* Arduino UNO的analogwrite和digitalwrite不能同时使用控制LED

* DHT11的out连接GPIO2,4可以，连接36,39都不行，连接GPIO2时，不能下载代码到ESP32,ESP32的各个GPIO 的功能很奇怪