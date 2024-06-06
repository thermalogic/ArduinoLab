# 飞思卡尔电源模块BTN7919B双驱动-电源驱动一体板


## ESP32 

![](img/esp32_pinout.jpg)

* 4,5,13,14,16-33 input/output 都可用

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


##  BTN7919B
BTN7919B板子可以 ：

* 输出：5V,3,3V电源

* 驱动2电机，1个舵机没有问题，

  * **问题:** Out2的out1侧的出口没有信号输出，LED指示灯亮，目前不能支持驱动2个电机

![](img/BTN7919B.jpg)

## BTN7919B双驱动

信号输入P1,p2,p3,p4都是PWM，对应out1（电机1）,out2（电机）

* P1-> out1线圈侧
* P2-> out1电源开关侧

* P3->out2的out1侧
* P4->out2的电源开关侧

此外，还有舵机PWM

在UNO中3，5，6，9，10，11 接口可以通过语句`analogWrite (pin, dutyCycle)`来实现一个指定占空比的 PWM

* 值在0～255之间，0为占空比0%，255为占空比100%，对应电压从0到+5V。                                                                            

## BTN7919B测试

### out1和舵机

P1-> out1线圈侧
P2-> out1电源开关侧
 
`test_btn7919_toycar_out1_turn.ino` 测试正常

### out2

`test_btn7919_toycar_out2.ino` 测试异常
 
 * out2开关侧-正常
 
 * out2靠out1侧-异常 - `有信号时，信号灯不亮`- `电压测试，没有接受到高电平信号`，原因不明！
  
 此外，电机2和电机1 似乎有联动关系？

`test_btn7919_toycar_out1_out2.ino` 测试异常

 * 因为out2靠out1侧-异常 - `有信号时，信号灯不亮`，和out1和out2同步动作时，信号灯也都不亮

PCB板子问题？ 可能是控制out2靠out1侧接口的BTN7919芯片有问题
