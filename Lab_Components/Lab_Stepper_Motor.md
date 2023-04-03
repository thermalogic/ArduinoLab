# 步进电机


## 电机和驱动

* 五线四相步进电机

The 28BYJ-48 Stepper Motor can draw up to 240 mA, 

* ULN2003 五线四相步进电机蓝色版

![](img/ULN-Driver1-1-300x272.png)

## 连线

使用Arduino IDE中的示例测试

* 驱动板上IN1、IN2、IN3、IN4分别连接UNO开发板的数字引脚8，9，10，11；
* 驱动板电源输入+、-引脚分别连接UNO开发板的5V、GND。

## 测试

程序通过ABCD四相通电顺序实现步进电机正反转控制。

步进电机旋转一周，程序中循环次数为什么是512次呢？这是根据我们使用的步进电机参数计算而来的：

* 步进电机电压5V，步距角5.625，减速比1：64

* 计算A-B-C-D通电一次转动的角度

5.625X2X4/64=0.703125

* 2是表示1相励磁方式每步是2倍的步距角，4表示走了4步， 64指电机减速比

* 转动360度循环ABCD通电的次数360/0.7031=512ails/88605767

##  参考

* https://www.circuitbasics.com/how-to-control-stepper-motors-with-uln2003-and-arduino-uno/