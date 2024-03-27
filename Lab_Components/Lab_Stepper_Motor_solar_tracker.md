# 基于步进电机的简易双轴光追踪器

* 光敏电阻检测光强，跟踪-使用AccelStepper步机电机库

* 步进电机是`开环控制`，舵机是闭环，所以，`单纯步进电机不能控制其初始位置`，因为没有位置信息反馈，需要配上霍尔编码器构成简单闭环
  所有，如果单纯用步进电机做光跟踪器，需要`人工`调整电机到初始位置,后面的转动相对于这个位置进行

* 步进电机是`开环控制`，所以，宜采用有光差是只向光强方向`转一个固定较角度`就停止，以简单的方式实现稳定转动

## 实现

### 源码 

* Lab_Simple_Dual_Axie_Light_Tracker_IRremote_Display.ino

### 功能
* 光追踪模式
  * 红外人工追踪
  * 自动追踪
* 红外遥控切换自动和人工追踪方式
* LCD显示
  * 4个光敏电阻的数据
  * 追踪模式：AUTO- 自动； IR - 红外人工遥控

### 红外遥控按键

*  上、下、左、右键遥控向相应方向转动
*  OK键在自动和人工转动方式之间转换

### 问题

`下`光敏电阻数据，偏小。

原因不明：其他几个型号不同？还是接地电阻大小问题？

* **解决**：现根据其他光敏电阻的数据，给其补偿350

##  元件

* 步进电机: 28BYJ-48 x2
* 步进电机驱动：ULN2003 x2
* 光敏电阻：5516 x4
* 电阻: 10K x4
* 万用板: 单面玻纤 9x15cm x1
* 面包板：830 x1
* 接线端子：2P x3
* Arduino UNO x1
* LCD: 1602A, I2C x1
* 红外遥控 
  * 接受器：VS1838B x1
  * 遥控器：中兴IPTV机顶盒(中国电信)遥控器  x1
* 支架：塑料瓶 x1，塑料瓶盖 x1
* M3铜柱、螺丝、螺母若干
* 面包板线，杜邦线若干  

## 光敏电阻连线

![](./img/Photoresistor-and-LED-WIRING-DIAGRAM-2-610x838.png)


## 电机和驱动

* 五线四相步进电机：The 28BYJ-48 Stepper Motor can draw up to 240 mA, 

* ULN2003 五线四相步进电机蓝色版

![](img/ULN-Driver1-1-300x272.png)

### 电机连线

使用Arduino IDE中的示例

* 驱动板上IN1、IN2、IN3、IN4分别连接UNO开发板的数字引脚8，9，10，11；
* 驱动板电源输入+、-引脚分别连接UNO开发板的5V、GND。

##  测试方案

### 面包板

简单的面包板测试

![](img/stepper_motor_solar_tracer.jpg)

面包板上光敏电阻，发送的信号，那边光强，电机就带动其上连接的纸板向那个方向转

### 洞洞板

洞洞板测试的原件布置：
* 光敏电阻焊接在洞洞板上。
 *  洞洞板上布置2个接线柱
     * 一个用于接电源
     * 一个用于输出2个光敏电阻的信号
* 步进电机驱动安装在小面包板上
  * 小面包板从Arduino引入电源，给电机和洞洞板供电
* 步进电机安装在食品塑料瓶上
* 步进电机轴连接亚克力板
* 洞洞板安装在亚克力板上

步进电机转动带动洞洞板向光强的一侧转动到2侧光强小于设定数值。

洞洞板不大，2侧光敏电阻在均匀光线情况下，数值差别不大，可以通过用手遮挡一个光敏电阻，使的2边差别变大，电机会转动板子移被遮挡的位置。

![](img/stepper_motor_solar_tracer_multiboard_1.jpg)

![](img/stepper_motor_solar_tracer_multiboard_2.jpg)

## 软件

### 不使用库

* `Lab_Stepper_Motor_Solar_Tracker_simple.ino` 
* `Lab_Stepper_Motor_Solar_Tracker.ino` 有较多判断，但是，还是没有处理好：越转2边光线强度差别越大问题

### 使用第三方库

* AccelStepper库

* `Lab_Stepper_Motor_Solar_Tracker_AccelStepper.ino` -  刷机用代码

### 解决问题

使用AccelStepper库不能改变方向，都向一个方向转! 
* https://www.airspayce.com/mikem/arduino/AccelStepper/

原因是`28byj-48`电机的motors连线特别

* **byj - `pins 2 and 3` swapped !!!**

所以，使用时需要

* Pins entered in sequence IN1-**`IN3`**-IN2-IN4 for proper step sequence
* use HALF4WIRE for half stepping

如Arduino pin: ULN2003A IN pin out pin color code on the byj stepper

* 8 in1 
* 9 in2 
* 10 in3
* 11 in4

那么代码如下：
```c
// byj - pins 2 and 3 swapped !!!
AccelStepper byj(AccelStepper::HALF4WIRE, 8, 10, 9, 11); 
```

## Dual-Axis Gimbal 双轴云台

**自做双轴云台结构**

* 垂直步进电机安装在瓶盖上 - 1 轴自由度
* 水平电机通过瓶盖连接垂直步进电机轴上- 2 轴自由度
   * 水平电机安装连轴器，多个M3铜柱通过连轴器的M3紧固空连接构成平板支

**测试代码：**  * 

* Lab_Simple_Dual_Axie.ino OK！

* Lab_Dual_Axies_Stepper_Motor_Solar_Tracker_AccelStepper.ino OK！

![](img/solar_tracer/my_dual_axie.jpg)

## 红外遥控

### 步进电机步进方式运行

* Lab_Simple_Dual_Axie_Gimbal_IRremote.ino

`TODO：` ：步进电机步进方式运行时，接受到一个旋转角度（步长）的命令后，在其执行需要时间，不能接受红外遥控命令中间停止
   另建立独立的`Lab_freeRTOS` ，尝试解决方法

### 步进电机使用通用电机运动模式

* Lab_Simple_Dual_Axie_Gimbal_IRremote_general_motor_model.ino

步进电机使用通用电机运动模式-不给运动步长，一直转动到接受到其他命令，立刻改变运动方向

## Mobatool库

* 该库的Example的Stepper-02对应28byj-48电机

## 使用1602A I2C显示信息

* `Lab_Simple_Dual_Axie_Gimbal_IRremote_1602A_I2C.ino`

电机转动时间，LCD显示闪动，可能是电机运行影响对LCD的供电？ 怎样改进？ 电源处加电容？？？

#
##  参考

* https://www.circuitbasics.com/how-to-control-stepper-motors-with-uln2003-and-arduino-uno/

* https://www.instructables.com/Building-an-Automatic-Solar-Tracker-With-Arduino-U/