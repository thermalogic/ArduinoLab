#  红外和Web控制的小车

基于Serial Communication Between Arduino Pro Mini and ESP-01实现Web控制的小车

* Lab_2WD_9_Mini_Web.ino

**TODO**

目前，接收指令，不同的LED状态反映执行情况，可以进一步集成为`WIFI`控制小车
* 加入超声
* 加入电机控制

但是端口不够，方法

* 减少LED,或者不控制车速，

* 使用 74HC595 扩展IO
  * https://www.instructables.com/Add-More-Digital-Inputs-and-Outputs-to-Your-Arduin/

## 功能

* ESP8266提供web服务，并将信息通过串口发送给Arduino Pro Mini

* Arduino Pro Mini使用用`软串口`和ESP8266通信

Arduino端有多个串口时，需要使用`软串口`和ESP8266通信

**注意**：红外库使用板载的pin13作为反馈信号灯，所以，`软串口`不使用pin13 

 使用如下代码，不使用pin13作为反馈信号灯，释放pin13和系统运行资源，不然，系统运行不稳定

 ```c
 IrReceiver.begin(IR_RECEIVE_PIN,  DISABLE_LED_FEEDBACK); //释放pin13
```


## 硬件布置

* Arduino Pro Mini和红外，LED等安装在一个小面包板上
* ESP8266使用一个小面包板

### 小面包板

```c
#define LED_Left 9
#define LED_Right 10
#define IR_RECEIVE_PIN 11
```

### ESP8266面包板

* ESP8266面包板 GND(黑色) -> 面包板 - （ProMini GND）
* ESP8266面包板 3.3V(红色) -> 面包板 + （ProMini VCC）

* ESP8266 RX(蓝色)  -> Pro Mini VCC pin2
* ESP8266 TX(黄色)  -> Pro Mini VCC pin12

```c
#define SS_RX 12  // 不能用13，红外库用作为反馈灯
#define SS_TX 2
```