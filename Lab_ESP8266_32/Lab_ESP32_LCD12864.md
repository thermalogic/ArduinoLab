# LCD12864 SPI Communication For ESP32


## Components

*  ESP32
* LCD 12864 Module

##  ESP32
板子的左侧不可用：9,10,11,34,35,36,39，余下可用的GPIO是8个
* 4,5,13,14,16-33 input/output 都可用

![](img/esp32_pinout.jpg)

## LCD12864 

屏型号：12864ZW, ZW - 带中文字库
* 128x64 with controller ST7920, (model 12864ZW).

128X64显示分辨率为128×64，内置8192个16*16点汉字，和128个16*8点ASCII字符集,可以显示8×4行16×16点阵的汉字。也可完成图形显示。

* `实例可以显示中文，但是和代码的内容不一样，原因不明`

https://www.adeept.com/blog/tutorials/lcd12864-spi-communication-for-arduino.html


![](img/12864/12864.jpg)


```c
static const int latchPin = 25;  // RS
static const int clockPin = 32;  // E
static const int dataPin = 33;   // R/W
```

| LCD12864 | Arduino  |
|----------|----------|
|  Vss	   |  GND     |
|  Vdd	   |  +5V     |
|  RS	     |  25       |   
|  R/W	   |  33	      | 
|  E       |	32       |
|  PSB     |	GND     |
|  BLA     |	+5V     |
|  BLK     |	GND     |


## Adeept_LCD12864RSPI Library 

The number of  UNO or mega2560 IO above ports are limited. We often need a lot of IO resources when do some complex experiments. On a blog we use the LCD12864 parallel communication interface which  occupies a lot of IO resources. In order to save the UNO and mega2560 the IO resources, Adeept uses a `SPI` communication
We provide the `AdeeptLCD12864RSPI` library which is easy to control with the LCD12864.

* https://www.adeept.com/blog/wp-content/uploads/2018/08/AdeeptLCD12864RSPI.zip

## 问题12864ZW不能调对比度

`电位器连接连接VO，但是，不能调对比度？`

现在的屏型号是：12864ZW, ZW - 带中文字库

* 128x64 with controller ST7920, (model 12864ZW).

* https://forum.arduino.cc/t/lcd-128x64-st7920-using-u8glib/130825/9

* https://forum.arduino.cc/t/st7920-lcd-display-problem/206750/6

### 原因

 L12864ZW屏在硬件上做死的，没有驱动芯片的电路，是不好调整的

**PCB板:** I can see why the contrast adjustment doesn't work. The `Vo` pin is not connected on your board because jumper `J1` is open (same as on mine), 

but unlike my board, yours does not have the 10K pot - although the pads have been tinned as though it should have been fitted.
Similarly, the Vout pin is not connected - it goes to the resistor at position R12, which is not fitted.

The best suggestion I have is to source a pot of the correct size to fit at VR1, and remove the 0 ohm resistor R6 which is shorting it out.
The pot on my board has a resistance of 18K end to end but is set at 2K. So a 10K pot (which is what the ST7920 datasheet shows) would be fine.

**解决方案：**

https://pic-microcontroller.com/using-digole-12864zw-lcd-with-pic18f/

For contrast you can use V0 (pin 3) by connecting it to Vdd through a 10k variable resistor. However to get it to work you will need to **enable jumper `J1`** from the back of the module as in the figure

![](img/components/12864/Using-Digole-12864ZW-LCD-with-PIC18F.jpg)

