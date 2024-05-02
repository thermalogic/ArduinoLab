# OLED 

* Arrduino UNO
* OLED SSD1315 0.96

## OLED SSD1315 0.96

![oled](img/oled_096_ssd1315.jpg)

## 测试

 * 使用库: u8g2

 * Arduino UNO连线

oled   UNO 
 GND -> GND
 VCC -> 5V
 SCL -> A5
 SDA -> A4

* 示例

u8g2->u8x8->hello world
u8g2->u8x8->graphtest

正常！

删除测试的oled型号前的注释
```c
U8X8_SSD1306_128X64_ALT0_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE); 	  
```


