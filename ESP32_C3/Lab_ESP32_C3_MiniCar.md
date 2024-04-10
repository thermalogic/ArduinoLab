# 基于ESP32-C3的Mini Car

## 电机驱动和ESP32连接

Motor Drive：DRV8833

* ESP32-C3

测试完成Left Motor

| DRV8833      |                |
|--------------|----------------|
| VM           |  +5 Power  公用|
| GND          | GND            | 
| STBY         |  +5 Power  公用|
| AIN1         |  GPIO 10 绿    | 
| AIN2         |   GPIO 3 黄    |

待测试Right Motor

| BIN1         |   GPIO   绿   |
| BIN2         |   GPIO  黄  |

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

* GPIO11 Pin 24，因为ESP32C3的GPIO11(VDD_SPI)默认功能是给flash供电,所以，不能用

* GPIO2、8、9是Strapping管脚；它们和芯片复位状态有关，在芯片的系统复位过程中，Strapping管脚对自己电平采样并存储到锁存器，一直保持到芯片掉电或关闭。避免把这几个端口使用到其它功能上。

* GPIO12-17通常用于SPI flash和PSRAM，不推荐用作其它用途；

* GPIO18、19默认用于USB-JTAG，如果用作GPIO将无法使用USB-JTAG；

* RTC：GPIO0-5可以在Deep-sleep模式时使用。

* ADC留给模拟量：GPIO00,01,02,03,04
* SCL,SDA留给I2C设备:GPIO 05,04
* UART_RX,TX留给串口通讯: Pin08,09
* boot: GPIO09
* USB; GPIO18,19
* 2路贴片LED指示灯:D4,D5(GPIO12,13)


小车计划使用GPIO
* DRV8833:GPIO02,03 
   ,06.07,11  standby：+5 Pin31 还是 GPIO08 HIGH/LOW待测试

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

* ANI1：AO1的逻辑输入控制端口，电平0-5V。 GPIO 10 绿 
* AIN2：AO2的逻辑输入控制端口，电平0-5V。GPIO 6  黄
* BNI1：BO1的逻辑输入控制端口，电平0-5V。 GPIO 7  绿
* BIN2：BO2的逻辑输入控制端口，电平0-5V。GPIO 11  黄

* AO1、AO2为1路H桥输出端口，接一个直流电机的两个脚。
  01 +  红色
* BO1、BO2为2路H桥输出端口，接另一个外直接电机的两个脚。
* GND：接地。
* `VM`：芯片和电机供电脚，电压范围2.7 V – 10.8 V。
* `STBY`：接地或悬空芯片不工作，无输出，接5V工作；电平0-5V。
* NC：空脚
                        
## Layout

Motor Drive：DRV8833

* ESP32-C

| DRV8833      |                |
|--------------|----------------|
| VM           |  +5 Power  公用|
| GND          | GND            | 
| STBY         |  +5 Power  公用|
| AIN1         |  GPIO 2 绿    |
| AIN2         |   GPIO 3 黄    |
| BIN1         |   GPIO 7  绿   |
| BIN2         |   GPIO 11 黄  |

* Motor

| DRV8833      |                |
|--------------|----------------|
| AO1         | Left Motor + 红 |
| AO2         | Right Motor - 黑 |
| BO1         |   GPIO 7  绿   |
| BO2         |   GPIO 11 黄  |

电机的旋转方向可以通过对这些输入施加逻辑高电平 (5V) 或逻辑低电平（接地）来控制。下面的真值表显示了输入如何影响驱动器输出。

输入1/输入3	输入2/输入4	旋转方向
低(0)	低(0)	电机关闭
高(1)	低(0)	向前
低(0)	高(1)	向后
高(1)	高(1)	电机关闭

## 降压模块


## 电源