#  基于ESP32和飞思卡尔BTN7919B驱动模块的履带车

## T200金属履带式坦克底盘

* https://detail.1688.com/offer/571430740572.html

![T200](img/T200.jpg)

* 铝合金底板 x1
* 铝合金驱动器轮(带连轴器) x2
* 铝合金承重轮（带轴承） x6
* 电机 x2
* 塑料履带：4x75cm (宽*长度)

### 底板

底板配置安装孔：
 
* 25/37mm电机 - 可安装为4WD小车
* S90和MG995/996伺服电机
* Arduino UNO
* NodeMCU lit

![](img/T200-Chassis.jpg)

### 直流有刷减速电机及霍尔码盘
   
* 12V330转25电机: HM-GM-25-370 12V330直流减速电机

![](img/T200-motor.jpg)

* 霍尔码盘

![](img/T200-hall_sensor.jpg)

## ESP32 

![](img/esp32_pinout.jpg)

* Recommended PWM GPIO pins on the ESP32: 2,4,12-19,21-23,25-27,32-33

## 飞思卡尔BTN7919B双驱动模块

BTN7919B双驱动板是：电源和电机驱动一体板

板子提供
* 输出：5V,3,3V电源
* 驱动: 2电机，1个舵机
* 编码器1/2输入输出
  
![](img/BTN7919B.jpg)

信号P1,p2,p3,p4都是PWM，对应out1（电机1- 右）,out2（电机2-左）

此外，还有舵机PWM

### 履带车电机连线

```c
 右电机 红线 -> 电机1 out1 线圈侧 -> BTN7919 PMW2 -> GPIO 33 黄色
 右电机 黑线 -> 电机1 out1 开关侧 -> BTN7919 PMW1 -> GPIO 32 绿色

 左电机 红线 -> 电机2 out2 开关侧 -> BTN7919 PMW4 -> GPIO 12 黄色
 左电机 黑线 -> 电机2 out2 线圈侧 -> BTN7919 PMW3 -> GPIO 14 绿色 
```

### 超声舵机连线

超声舵机S90连接到BTN7919B

* BTN7919B舵机PWM -> GPIO 2

![](img/s90_servo.jpg)

## 电池

锂电池：11.4V,4200mAh

## 其他

* DHT11
* OLED

### DHT11

```c
#define DHTPIN 15
```

### I2C oled  

|I2C oled|	ESP32|
|------|------|
|GND   | GND  |
|VCC   | 3.3  |
|SCL   | GPIO 22|
|SDA   | GPIO 21|



