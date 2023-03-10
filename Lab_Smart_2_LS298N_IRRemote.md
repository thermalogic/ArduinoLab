# 智能小车2 - 红外遥控智能小车

  车速度太快，远红的发射器信号弱。控制不稳定，不方便测试。
  
  可以让每个前进后退动作运行2秒后停止。以方便测试

  * 用LED指示转向，3个LED使用了3个pins,板子的pins资源有限，如果还要连接其他传感器可以，除去LED,释放3个pin资源

## 添加红外遥控

在实验的的Arduino板子上，加一个扩展版

* 红外遥控原件安装在扩展版上的小面包版中
、
白遥控器：2 - 0x18 4- 0x8 6 0x5A 8 0x52 stop CH 0x46
黑遥控器：2 -0x11 4 - 0x14 6- 0x1 8 0x19 stop 0x0
华为盒子 ^ -0xCA4  <- 0x99 -> 0xC1 back 0xD2 stop(ok) 0xCE
**黑遥控器没有电了**

## 代码

```c

/*
 * Specify which protocol(s) should be used for decoding.
 * If no protocol is defined, all protocols (except Bang&Olufsen) are active.
 * This must be done before the #include <IRremote.hpp>
 */

#define DECODE_NEC          // Includes Apple and Onkyo

#define LED_Left 8
#define LED_Right 9
#define LED_Back 10

#define LeftForward 4   // Motor Black -     LS298N IN1 -> Arduino Pin4 
#define LeftBack 5      // Motor Red     +     LS298N IN2 -> Arduino Pin5 
#define RightForward 6  // Motor Black -     LS298N IN3 -> Arduino Pin6 
#define RightBack 7    // Motor Red     +     LS298N IN4 -> Arduino Pin7 

#include <Arduino.h>

#include "PinDefinitionsAndMore.h" // Define macros for input and output pin etc.
#include <IRremote.hpp>

#define  IR_RECEIVE_PIN 11

void setup() {
    pinMode(LED_Left, OUTPUT);
    pinMode(LED_Right, OUTPUT);
    pinMode(LED_Back, OUTPUT);
    Serial.begin(115200);
    // Just to know which program is running on my Arduino
    Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));

    // Start the receiver and if not 3. parameter specified, take LED_BUILTIN pin from the internal boards definition as default feedback LED
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

    Serial.print(F("Ready to receive IR signals of protocols: "));
    printActiveIRProtocols(&Serial);
    Serial.println(F("at pin " STR(IR_RECEIVE_PIN)));
    // motor
    pinMode(LeftForward,OUTPUT);
    pinMode(LeftBack,OUTPUT);
    pinMode(RightForward,OUTPUT);
    pinMode(RightBack,OUTPUT);
    initCar();
}

//  ------   motor
void initCar(){
	//默认全是低电平 停止状态
  digitalWrite(LeftForward,LOW); 
	digitalWrite(LeftBack,LOW);
	digitalWrite(RightForward,LOW); 
	digitalWrite(RightBack,LOW);
}

void go(){
  // 左轮前进
  digitalWrite(LeftForward,HIGH); 
	digitalWrite(LeftBack,LOW); 
  // 右轮前进
	digitalWrite(RightForward,HIGH); 
	digitalWrite(RightBack,LOW); 
}

void back(){
  //左轮后退
  digitalWrite(LeftForward,LOW); 
	digitalWrite(LeftBack,HIGH); 
  //右轮后退
	digitalWrite(RightForward,LOW); 
	digitalWrite(RightBack,HIGH); 
}

/* 左转 */
void turnLeft(){
  //左轮不动
  digitalWrite(LeftForward,LOW); 
	digitalWrite(LeftBack,LOW);
  // 右轮前进
	digitalWrite(RightForward,HIGH); 
	digitalWrite(RightBack,LOW); 
}

/* 右转 */
void turnRight(){
  // 左轮前进
  digitalWrite(LeftForward,HIGH); 
	digitalWrite(LeftBack,LOW); 
  // 右轮不动
  digitalWrite(RightForward,LOW); 
	digitalWrite(RightBack,LOW);
}

void stopCar(){
	initCar();
}

void loop() {
    /*
     * Check if received data is available and if yes, try to decode it.
     * Decoded result is in the IrReceiver.decodedIRData structure.
     *
     * E.g. command is in IrReceiver.decodedIRData.command
     * address is in command is in IrReceiver.decodedIRData.address
     * and up to 32 bit raw data in IrReceiver.decodedIRData.decodedRawData
     */
    if (IrReceiver.decode()) {

        /*
         * Print a short summary of received data
         */
        IrReceiver.printIRResultShort(&Serial);
        IrReceiver.printIRSendUsage(&Serial);
        if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
            Serial.println(F("Received noise or an unknown (or not yet enabled) protocol"));
            // We have an unknown protocol here, print more info
            IrReceiver.printIRResultRawFormatted(&Serial, true);
        }
        Serial.println();

        /*
         * !!!Important!!! Enable receiving of the next value,
         * since receiving has stopped after the end of the current received data packet.
         */
        IrReceiver.resume(); // Enable receiving of the next value

        /*
         * Finally, check the received data and perform actions according to the received command
         */
        if (IrReceiver.decodedIRData.command == 0x11) {
            // forward - 2
             digitalWrite(LED_Left, HIGH);  
             digitalWrite(LED_Right, HIGH);  
            digitalWrite(LED_Back, LOW);  
            go();
            
        } else if (IrReceiver.decodedIRData.command == 0x14) {
            // Left - 4 
            digitalWrite(LED_Left, HIGH);  
            digitalWrite(LED_Right, LOW);  
            digitalWrite(LED_Back, LOW);  
            turnLeft();
       
        } else if (IrReceiver.decodedIRData.command == 0x16) {
            // right - 6 
            digitalWrite(LED_Left, LOW);  
            digitalWrite(LED_Right, HIGH); 
            digitalWrite(LED_Back, LOW);   
            turnRight();
        } else if (IrReceiver.decodedIRData.command == 0x19) {
            // back  
             digitalWrite(LED_Left, LOW);  
             digitalWrite(LED_Right, LOW);  
             digitalWrite(LED_Back, HIGH);  
             back();
        } else if (IrReceiver.decodedIRData.command == 0x0) {
            // stop  
            digitalWrite(LED_Left, LOW);  
            digitalWrite(LED_Right, LOW);  
            digitalWrite(LED_Back, LOW);  
            stopCar();

        }
    }
}


```