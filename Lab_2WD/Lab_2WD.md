# 2WD小车制作


## 问题：红外接受器接受噪声

TODO:

* 用74CH595的元件多,电路复杂的方案，其 红外接受器，接受遥控器的信号不稳定，多为噪声，原因不明。

提问的很多，目前，还没有解决问题

* How solid is your power supply? Those IR receivers are VERY FUSSY about power.
  If your +5 is soft or a little low the Arduino won't care but the IR RXVR will!

## 制作步骤

1. 小车初步安装
2. 测试各模块:电机驱动L289N、红外遥控和超声测距
3. 给小车加入：红外遥控和超声测距 模块
4. 小车模块集成

## 初步小车安装

1. 安装全向小轮。 **注意**： 全向小轮的高度小于小车橡胶轮，所以，需要通过铜柱连接都车架上，提高高度和橡胶轮一致
2. 焊接TT电机电源线。**注意**：TT电机相对两边的，应该都是红色电源线在上为宜，目前，2侧不一致，左侧电机红色在下，以后可能**重新焊**
3. 安装TT电机
4. 安装电机驱动L289N - 小车后部
5. 安装电池  
6. 安装Arduino - Arduino使用自做的一层板子置于电池之上，小车的中间位置

## 测试各模块

###  在初步安装的小车测试：电机驱动L289N

* 先在没有软件的情况下，测试硬件及其连线
* 然后，测试软件

### 在一个面包板上测试：红外遥控和超声测距

## 给小车加入红外遥控和超声测距模块

将测试的面包包放到小车上，连线到小车上的Arduino板子上

##  小车模块集成

小车模块集成：红外遥控、超声测距和电机控制

### 代码

单模块测试和合成，共有6个程序代码，如下：

1. 电机驱动L289N测试代码 ：Lab_2WD_1-LS298N_two_wheel.ino
2. 红外遥控测试代码 : Lab_2WD_2-IRremote_leds.ino
3. 超声测距代码: Lab_2WD_3-Ultrasonic.ino
4. 红外遥控小车代码(1+2): Lab_2WD_4_Motor_IRremote_leds.ino
5. 红外遥控 + 超声避障小车代码(4+3): Lab_2WD_5_Motor_IRremote_Ultrasonic.ino
6. 电机速度控制: Lab_2WD_6_Motor_SpeedControl.ino
7. 红外遥控 + 超声避障小车代码+速度控制(5+6):Lab_2WD_7_Motor_IR_Ultra_Speed.ino
8. 红外遥控 + 超声避障小车代码 + 速度控制 + LED闪烁(7+LED闪烁):Lab_2WD_8_Motor_IR_Ultra_Speed_blinks.ino

### 模块和Arduino连线

* **电源**：电池向LS298N供电; LS298N供电向Arduino供电

* **Arduio端口资源使用**： 空余1,2还没有使用 

1. 电机、LN298和Arduino连线

LN298N使用了Arduino： pin3,4 ；pin7,8和pin5,6

* pin3,4；pin7,8控制前后
* pin5,6控制速度

```c

#define LeftForward 3  // Motor Red +   LS298N IN4 -> Arduino Pin3
#define LeftBack 4     // Motor  black - LS298N IN3 -> Arduino Pin4
#define RightForward 8   // Motor balck -  LS298N IN1-> Arduino Pin8
#define RightBack 7      // Motor red +   LS298N IN2 -> Arduino Pin7

#define leftPWM 5
#define rightPWM 6

int speed_level1= 125; // 转向时用，转速差，转向
int speed_level2= 200; // 太低驱动不了，调试后200比较合适，不太快，也不慢
```

*  左电机的向前和右不一致。 右电机是Motor Red + 向前，目前用代码处理不一致， 以后，可以重新焊左电机电源线，交换红、黑电源线的位置


2. 红外遥控


红外输出 -> 11

```c
#define IR_RECEIVE_PIN 11 //IRremote.hpp  默认是pin2，小车使用pin11
```

3. 超声

tric -> pin12
echo -> pin13

```c
int trigPin = 12;    // Trigger
int echoPin = 13;    // Echo
```
4. LED

left led -> pin9
right led -> pin10

