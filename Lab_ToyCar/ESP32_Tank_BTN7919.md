# 飞思卡尔电源模块BTN7919B双驱动-电源驱动一体板

## ESP32 

![](img/esp32_pinout.jpg)

##  BTN7919B双驱动

BTN7919B板子可以 ：

* 输出：5V,3,3V电源
* 驱动: 2电机，1个舵机
  
![](img/BTN7919B.jpg)

信号P1,p2,p3,p4都是PWM，对应out1（电机1- 右）,out2（电机2-左）

此外，还有舵机PWM

* Recommended PWM GPIO pins on the ESP32 include: 2,4,12-19,21-23,25-27,32-33

### 电机

```c
 右电机 红线 -> 电机1 out1 线圈侧 -> BTN7919 PMW2 -> GPIO 33 黄色
 右电机 黑线 -> 电机1 out1 开关侧 -> BTN7919 PMW1 -> GPIO 32 绿色

 左电机 红线 -> 电机2 out2 开关侧 -> BTN7919 PMW4 -> GPIO 12 黄色
 左电机 黑线 -> 电机2 out2 线圈侧 -> BTN7919 PMW3 -> GPIO 14 绿色 
```

### 舵机

超声舵机S90连接到BTN7919B

* BTN7919B舵机PWM -> GPIO 2

![](img/s90_servo.jpg)


## DHT11

```c
#define DHTPIN 15
```
## I2C oled  

|I2C oled|	ESP32|
|------|------|
|GND   | GND  |
|VCC   | 3.3  |
|SCL   | GPIO 22|
|SDA   | GPIO 21|




