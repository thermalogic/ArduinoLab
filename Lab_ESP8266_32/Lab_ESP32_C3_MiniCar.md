# 基于ESP32-C3的Mini Car

## ​Components

* ESP32-C3 X1
* Motor Drive：DRV8833 x1
* IR Kit: Receiver and Remote Controller 
  * Receiver：VS1838B x1
  * Remote Controller: [21 Keys](https://hobbycomponents.com/wired-wireless/464-low-profile-21-button-infrared-ir-remote)  x1
* Ultrasonic Sensor：HC-SR04 x1   
* 2WD Robotic Car Kit (2 wheels, 2 motors, and a chassis) x1 
* Power: 18680 X2

## ESP32-C3

* https://wiki.luatos.com/chips/esp32c3/board.html

### 硬件资源

* 尺寸长宽 21mm*51mm

* 1路SPI FLASH，板载4MB，支持最高 16MB

* 2路UART接口，UART0~UART1,其中下载口为UART0

* 5路12比特 ADC，最高采样率 100KSPS:GPIO00,04

* 1路低速SPI接口，支持主模式

* 1路IIC控制器

* 4路PWM接口,可使用任意GPIO

* GPIO外部管脚15路，可复用

* 2路贴片LED指示灯:D4,D5(GPIO12,13)

* 1路复位按键+1路BOOT按键

* 1路USB转TTL下载调试口

* 2.4G PCB板载天线

## GPIO
![](img/esp32-c3.jpg)

任意GPIO均可作为PWM脚, 编号与GPIO一致, 但同时只能开启`4路PWM`,务必注意

* ADC留给模拟量：GPIO00,01,02,03,04
* SCL,SDA留给I2C设备:GPIO 05,04
* UART_RX,TX留给串口通讯: Pin08,09
* boot: GPIO09
* USB; GPIO18,19
* 2路贴片LED指示灯:D4,D5(GPIO12,13)

小车计划使用GPIO
* DRV8833:GPIO10,06.07,11  standby：+5 Pin31 还是 GPIO08 HIGH/LOW待测试

红外和超声的GPIO待实际测试，确定使用那些
* IR:GPIO13，使用排座接入 
* ultrasonic:GPIO 2,18


### 供电电源

CORE-ESP32-C3核心板支持以下3种方式供电：

* Type-C 接口供电（默认）

* 5V和GND排针供电: Pin31,Pin32

* 3V3 和 GND 排针供电

调试过程中优先推荐的供电方式：TYPE-C USB接口供电。

### 
ESP32-C3 Pin USB Signal

GPIO18 D-  白色

GPIO19 D+  绿色

5V  V_BUS

GND  Ground

## 电机驱动DEV8833

## NRV8833

![](img/DRV8833_Pinout.jpg)

## NRV8833 layout

![](img/DRV8833-Dual-Driver-Circuit.jpg)

管脚说明：
* ANI1：AO1的逻辑输入控制端口，电平0-5V。
* AIN2：AO2的逻辑输入控制端口，电平0-5V。
* BNI1：BO1的逻辑输入控制端口，电平0-5V。
* BIN2：BO2的逻辑输入控制端口，电平0-5V。

* AO1、AO2为1路H桥输出端口，接一个直流电机的两个脚。
* BO1、BO2为2路H桥输出端口，接另一个外直接电机的两个脚。
* GND：接地。
* `VM`：芯片和电机供电脚，电压范围2.7 V – 10.8 V。
* `STBY`：接地或悬空芯片不工作，无输出，接5V工作；电平0-5V。
* NC：空脚
                        
原文链接：https://blog.csdn.net/m0_51388102/article/details/127399902
## 降压模块


## 电源