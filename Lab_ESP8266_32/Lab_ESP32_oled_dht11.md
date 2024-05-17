# ESP32综合实验-oled温湿度测量

## 元件

* 0.96 oled蓝色(板载)
* 温湿度:DHT11

## ESP32 

![](img/esp32_pinout.jpg)

* 4,5,13,14,16-33 input/output 都可用

## 元件连接

* DHT11
```c
#define DHTPIN 15
```

* i2c oled  

|I2C oled|	ESP32|
|------|------|
|GND   | GND  |
|VCC   | 3.3  |
|SCL   | GPIO 22|
|SDA   | GPIO 21|

## 代码

1. 使用Adafruit库

```c
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeMonoBold18pt7b.h>
```
Lab_ESP32_oled_dht11_2.ino

2. 使用U8g2lib库

```c
#include <U8g2lib.h>
U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
```

Lab_ESP32_oled_dht11_1.ino