# Monochrome Nokia 5110 LCD Displays

## 使用Adafruit库测试

在线安装时，部分从githua 下载会失败，可以下载器zip文件，然后，通过include库的方式加入库

```c
// Software SPI (slower updates, more flexible pin options):
// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);
```