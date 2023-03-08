# 智能小车3 - 超声避撞

## 超声连接

单独连接 Arduino 
 Module HR-SC04 (four pins)  attached to digital pins as follows:
 
  
 | HC-SR04 | Arduino |    
 |---------|---------|   
 |   Vcc   |   5V    |   
 |   Trig  |   12    | 
 |   Echo  |   13    | 
 |   Gnd   |   GND   |

 ## 超声加入小车连接

 超声模块使用一个小面包板，放在车头，然后，连接Arduino 和超声模块小面包板

*  信号线接入 Arduino 
| HC-SR04 | Arduino |   
 |   Trig  |   12    | 
 |   Echo  |   13    | 

* 电源从超声模块小面包板进入
 | HC-SR04 | 超声模块小面包板|    
 |---------|---------|   
 |   Vcc   |   5V    |   
 |   Gnd   |   GND   |

 ## 代码

 ```c


/*   
  红外遥控：前进，后退，左右转向
   超声避撞：检测距离20cm时停止运行，采用的是最简单避撞方式：停车
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

#define trigPin  12    // Trigger
#define echoPin  13    // Echo
long duration, cm;

void setup() {
    pinMode(LED_Left, OUTPUT);
    pinMode(LED_Right, OUTPUT);
    pinMode(LED_Back, OUTPUT);

      //Define ultrasonoc inputs and outputs
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

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

void get_distance(){
// ultrasonic
// The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
  // Convert the time into a distance
  cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
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
  digitalWrite(LeftForward,200);  //HIGH
	digitalWrite(LeftBack,LOW); 
  // 右轮前进
	digitalWrite(RightForward,200); 
	digitalWrite(RightBack,LOW); 
}

void back(){
  //左轮后退
  digitalWrite(LeftForward,LOW); 
	digitalWrite(LeftBack,200); 
  //右轮后退
	digitalWrite(RightForward,LOW); 
	digitalWrite(RightBack,200); 
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
     delay(100);
     get_distance();
     
    if (cm<20)
     {
        stopCar();     
     }
  
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
        if (IrReceiver.decodedIRData.command == 0xCA) {
            // forward - 2
            digitalWrite(LED_Left, HIGH);  
            digitalWrite(LED_Right, HIGH);  
            digitalWrite(LED_Back, LOW);  
            go();
             
        } else if (IrReceiver.decodedIRData.command == 0x99) {
            // Left - 4 
            digitalWrite(LED_Left, HIGH);  
            digitalWrite(LED_Right, LOW);  
            digitalWrite(LED_Back, LOW);  
            turnLeft();
       
        } else if (IrReceiver.decodedIRData.command == 0xC1) {
            // right - 6 
            digitalWrite(LED_Left, LOW);  
            digitalWrite(LED_Right, HIGH); 
            digitalWrite(LED_Back, LOW);   
            turnRight();
        } else if (IrReceiver.decodedIRData.command == 0xD2) {
            // back  
             digitalWrite(LED_Left, LOW);  
             digitalWrite(LED_Right, LOW);  
             digitalWrite(LED_Back, HIGH);  
             back();
       } else if (IrReceiver.decodedIRData.command == 0xCE) {
            // stop  
            digitalWrite(LED_Left, LOW);  
            digitalWrite(LED_Right, LOW);  
            digitalWrite(LED_Back, LOW);  
            stopCar();

        };
    }
 
}

 ```