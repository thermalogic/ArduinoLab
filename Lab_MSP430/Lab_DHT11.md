# DHT11

## 安装DHT11驱动

安装支持MSP430的DHT11驱动库

* https://github.com/DFRobot/DFRobot_DHT11

 ## layout

|  DHT11  |  EXP430F5529LP |
|:-------:|:--------------:|
|    +    |        +5V     |
|    -    |        GND     |
|   out   |   P1.6(5 or P1_6)|

## 实例

实例代码运行输出的温度，为华氏度，转换为摄氏度

$$(DHT.temperature-32)/1.8$$

```c
#include <DFRobot_DHT11.h>
DFRobot_DHT11 DHT;
#define DHT11_PIN 5

void setup(){
  Serial.begin(9600);
}

void loop(){
  DHT.read(DHT11_PIN);
  Serial.print("temp:");
  Serial.print((DHT.temperature-32)/1.8);
  Serial.print("  humi:");
  Serial.println(DHT.humidity);
  delay(1000);
}
```