##  7-segment display modules based on the TM1637


An Arduino library for 7-segment display modules based on the TM1637 chip, such as Seeed Studio's Grove 4 digit display. The TM1637 chip also has keyboard input capability, but it's not implemented in this library.

![](img/TM1637.jpg)

## Arduino library for TM1637 (LED Driver)

https://github.com/avishorp/TM1637

* 直接使用其例程测试即可

* 连线
```c
// Module connection pins (Digital Pins)
#define CLK 2
#define DIO 3
```
实现了心率测量的数码管显示

* TM1637_heatrate.ino
