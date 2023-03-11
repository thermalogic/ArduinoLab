# 智能小车1- 使用Arduino加L298N控制智能小车直流电机

##  基本步骤

* 准备电机和车架

* LS298N控制智能小车直流电机:前进，后退，左右转

* 红外遥控（可以加led表示)

* 测速

* 调速

* 超声避撞

## 实现代码

每个功能都有基本代码

目前综合了：红外遥控 + led表示 + 超声 + 测速的代码是

  * Lab_LS298N_IRremote_leds_ultrasonic_speed.ino

## 保留的pins问题

如果加入调速需要使用2个Pin, 红外遥控 + led表示 + 超声 + 测速后，Arduino不够

* LS298N ENA -> Arduino UNO 9，“
* LS298N ENB -> Arduino UNO 10

和led的pin冲突，需要减少led的pins
 

**`暂时保留led,不烧录调速代码，以后，可以删除led, 同时加入，红外遥控车速命令`**
