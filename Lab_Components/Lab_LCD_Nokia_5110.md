# Monochrome Nokia 5110 LCD Displays


* https://simple-circuit.com/arduino-nokia-5110-lcd-dht11-sensor/

* https://randomnerdtutorials.com/complete-guide-for-nokia-5110-lcd-with-arduino/

* https://fritzing.org/projects/nokia5110-lcd-with-dht11-temperature-and-humidity

## Nokia 5110 LCD Displays

![](img/LCD5110/LCD5110_pins.jpg)

1) RST – Reset                  Pin3
2) CE – Chip Enable             Pin4 
3) D/C – Data/Command Selection Pin5
4) DIN – Serial Input           Pin6    
5) CLK – Clock Input            Pin7
6) VCC – 3.3V                 -3.3V 
7) LIGHT – Backlight Control - +5V 
8) GND – Ground               GND 

layout

```c
// Software SPI (slower updates, more flexible pin options):
// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
```


如下连接：
 *  LIGHT – Backlight Control - +5V
*   GND – Ground               GND 
背光不亮

![](img/LCD5110/LCD5110_layout.jpg)

## 驱动库

驱动库使用Adafruit的库

在线安装时，部分从githua 下载会失败，可以下载器zip文件，然后，通过include库的方式加入库

## 5110+DHT11

![](img/LCD5110/LCD5110_DHT11_layout.jpg)

##  背光的问题

如下连接时：
 *  LIGHT – Backlight Control - +5V
*   GND – Ground               GND 
背光不亮，显示完整

如果需要背光亮，需要给但是，LIGHT加上电位器，调节亮度
LIGHT – Backlight Control - 电位器out

但亮度高时,有时正常，内容有时显示不完整，亮度低时情况较好，

* 可能排针没有焊接好
* pin3-7在背光使用电器器时间，应该使用电阻

![](img/LCD5110/LCD5110_DHT11_backgight_layout.jpg)

![](img/LCD5110/LCD5110_DHT11_backgight_demo.jpg)