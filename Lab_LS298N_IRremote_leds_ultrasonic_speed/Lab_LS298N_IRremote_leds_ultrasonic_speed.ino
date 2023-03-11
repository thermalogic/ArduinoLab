
/*   
  红外遥控：前进，后退，左右转向
   超声避撞：检测距离20cm时停止运行，采用的是最简单避撞方式：停车
 */

#define DECODE_NEC  // Includes Apple and Onkyo

// led指示
#define LED_Left 8
#define LED_Right 9
#define LED_Back 10

// 测速 left int1 pin3,
//      right: int0 pin2
int leftCounter = 0, rightCounter = 0;
unsigned long time = 0, old_time = 0;  // 时间标记
unsigned long time1 = 0;               // 时间标记
float lv, rv;       


#define LeftForward 4   // Motor Black -     LS298N IN1 -> Arduino Pin4
#define LeftBack 5      // Motor Red     +     LS298N IN2 -> Arduino Pin5
#define RightForward 6  // Motor Black -     LS298N IN3 -> Arduino Pin6
#define RightBack 7     // Motor Red     +     LS298N IN4 -> Arduino Pin7

#include <Arduino.h>

#include "PinDefinitionsAndMore.h"  // Define macros for input and output pin etc.
#include <IRremote.hpp>

#define  IR_RECEIVE_PIN 11

#define trigPin 12  // Trigger
#define echoPin 13  // Echo
long duration, cm;

void setup() {
  pinMode(LED_Left, OUTPUT);
  pinMode(LED_Right, OUTPUT);
  pinMode(LED_Back, OUTPUT);

  //Define ultrasonoc inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(115200);

   // 测速
  attachInterrupt(0, RightCount_CallBack, FALLING);
  attachInterrupt(1, LeftCount_CallBack, FALLING);
  
  // Just to know which program is running on my Arduino
  Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));

  // Start the receiver and if not 3. parameter specified, take LED_BUILTIN pin from the internal boards definition as default feedback LED
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

  Serial.print(F("Ready to receive IR signals of protocols: "));
  printActiveIRProtocols(&Serial);
  Serial.println(F("at pin " STR(IR_RECEIVE_PIN)));
  // motor
  pinMode(LeftForward, OUTPUT);
  pinMode(LeftBack, OUTPUT);
  pinMode(RightForward, OUTPUT);
  pinMode(RightBack, OUTPUT);
  initCar();
}

/*
 * *速度计算
 */
bool SpeedDetection() {
  time = millis();                   //以毫秒为单位，计算当前时间
  if (abs(time - old_time) >= 1000)  // 如果计时时间已达1秒
  {
    detachInterrupt(0);  // 关闭外部中断0
    detachInterrupt(1);  // 关闭外部中断1
    //把每一秒钟编码器码盘计得的脉冲数，换算为当前转速值
    //转速单位是每分钟多少转，即r/min。这个编码器码盘为20个空洞。
    lv = (float)leftCounter * 60 / 20;   //小车车轮电机转速
    rv = (float)rightCounter * 60 / 20;  //小车车轮电机转速
    Serial.print("left:");
    Serial.print(lv);  //向上位计算机上传左车轮电机当前转速的高、低字节
    Serial.print("     right:");
    Serial.println(rv);  //向上位计算机上传左车轮电机当前转速的高、低字节
    //恢复到编码器测速的初始状态
    leftCounter = 0;  //把脉冲计数值清零，以便计算下一秒的脉冲计数
    rightCounter = 0;
    old_time = millis();  // 记录每秒测速时的时间节点
    // 测速 left int1 pin3,
    //  right: int0 pin2
    attachInterrupt(0, RightCount_CallBack, FALLING);  // 重新开放外部中断0
    attachInterrupt(1, LeftCount_CallBack, FALLING);   // 重新开放外部中断0
    return 1;
  } else
    return 0;
}

/*
 * *左轮编码器中断服务函数
 */
void LeftCount_CallBack() {
  leftCounter++;
}

/*
 * *右轮编码器中断服务函数
 */
void RightCount_CallBack() {
  rightCounter++;
}


void get_distance() {
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
  cm = (duration / 2) / 29.1;  // Divide by 29.1 or multiply by 0.0343
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
}

void led_forward() {
  digitalWrite(LED_Left, HIGH);
  digitalWrite(LED_Right, HIGH);
  digitalWrite(LED_Back, LOW);
}

void led_turnLeft() {
  digitalWrite(LED_Left, HIGH);
  digitalWrite(LED_Right, LOW);
  digitalWrite(LED_Back, LOW);
}

void led_turnRight() {
  digitalWrite(LED_Left, LOW);
  digitalWrite(LED_Right, HIGH);
  digitalWrite(LED_Back, LOW);
}

void led_back() {
  digitalWrite(LED_Left, LOW);
  digitalWrite(LED_Right, LOW);
  digitalWrite(LED_Back, HIGH);
}

void led_stop() {
  digitalWrite(LED_Left, LOW);
  digitalWrite(LED_Right, LOW);
  digitalWrite(LED_Back, LOW);
}

//  ------   motor
void initCar() {
  //默认全是低电平 停止状态
  digitalWrite(LeftForward, LOW);
  digitalWrite(LeftBack, LOW);
  digitalWrite(RightForward, LOW);
  digitalWrite(RightBack, LOW);
}

void go() {
  // 左轮前进
  digitalWrite(LeftForward, 125);  //HIGH
  digitalWrite(LeftBack, LOW);
  // 右轮前进
  digitalWrite(RightForward, 125);
  digitalWrite(RightBack, LOW);
}

void back() {
  //左轮后退
  digitalWrite(LeftForward, LOW);
  digitalWrite(LeftBack, 200);
  //右轮后退
  digitalWrite(RightForward, LOW);
  digitalWrite(RightBack, 200);
}

/* 左转 */
void turnLeft() {
  //左轮不动
  digitalWrite(LeftForward, LOW);
  digitalWrite(LeftBack, LOW);
  // 右轮前进
  digitalWrite(RightForward, HIGH);
  digitalWrite(RightBack, LOW);
}

/* 右转 */
void turnRight() {
  // 左轮前进
  digitalWrite(LeftForward, HIGH);
  digitalWrite(LeftBack, LOW);
  // 右轮不动
  digitalWrite(RightForward, LOW);
  digitalWrite(RightBack, LOW);
}

void stopCar() {
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
  // 测速
  SpeedDetection();
  
  get_distance();
  if (cm < 25) {
    stopCar();
  }
  delay(100);



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
    IrReceiver.resume();  // Enable receiving of the next value

    /*
         * Finally, check the received data and perform actions according to the received command
         */
    if (IrReceiver.decodedIRData.command == 0xCA) {
      // forward
      led_forward();
      go();

    } else if (IrReceiver.decodedIRData.command == 0xC1) {
      // Left
      led_turnLeft();
      turnLeft();

    } else if (IrReceiver.decodedIRData.command == 0x99) {
      // right
      led_turnRight();
      turnRight();
    } else if (IrReceiver.decodedIRData.command == 0xD2) {
      // back
      led_back();
      back();
    } else if (IrReceiver.decodedIRData.command == 0xCE) {
      // stop
      led_stop();
      stopCar();
    };
  }
}
