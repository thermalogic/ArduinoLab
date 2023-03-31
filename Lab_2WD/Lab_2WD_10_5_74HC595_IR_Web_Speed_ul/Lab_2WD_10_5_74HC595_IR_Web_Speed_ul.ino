#include "PinDefinitionsAndMore.h" // Define macros for input and output pin etc.
#include <IRremote.hpp>
#include <SoftwareSerial.h>

#define DECODE_NEC // Includes Apple and Onkyo
#define IR_RECEIVE_PIN 7

int latchPin = 13; // Latch pin of 74HC595 is connected to Digital pin 13
int clockPin = 4;  // Clock pin of 74HC595 is connected to Digital pin 4
int dataPin = 12;  // Data pin of 74HC595 is connected to Digital pin 12

byte values = 0; // Variable to hold the pattern of which LEDs are currently turned on or off

// 74hc595
#define MOTOR_LEFT_FORWARD 4
#define MOTOR_LEFT_BACK 3
#define MOTOR_RIGHT_FORWARD 1
#define MOTOR_RIGHT_BACK 2
#define LED_LEFT 5
#define LED_RIGHT 6
// arduino
#define leftPWM 6
#define rightPWM 5

// motor state code
#define MOTOR_GO 0
#define MOTOR_BACK 1
#define MOTOR_STOP 2
#define MOTOR_LEFT 3
#define MOTOR_RIGHT 4

int motor_state = MOTOR_STOP;
int motor_cmd = MOTOR_STOP;

// 电机速度PWM数值
// 数值太小，电池电量不足，驱动不了，需要取适当的数值
int left_speed_level1 = 45; // 转向时用，转速差，转向
int right_speed_level1 = 50;
int left_speed_level2 = 130; // 同样PWM数值,左右电机速度会有差别，车子会向慢的一边转,可以测试两边一样速度的各自PWM数值
int right_speed_level2 = 135;
int left_speed_level3 = 245;
int right_speed_level3 = 255;

long previousMillis; // leds闪烁用变量

// softserial 传递的控制电机运行状态的控制字符
String GO = "G";
String STOP = "S";
String BACK = "B";
String LEFT = "L";
String RIGHT = "R";
// softserial
#define SS_RX 10
#define SS_TX 11
SoftwareSerial mySerial(SS_RX, SS_TX);

// 测速变量 -Arduino UNO/Pro Mini使用中断0，1 占用pin2,3
int leftCounter = 0, rightCounter = 0;
unsigned long time = 0, old_time = 0; // 时间标记
unsigned long time1 = 0;              // 时间标记
float lv, rv;                         // 左、右轮速度

// 超声
#define TRIG_PIN 8 // Trigger
#define ECHO_PIN 9 // Echo
long duration, cm;

// 74HC595N
void shift_register_update()
{
  //
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, values);
  digitalWrite(latchPin, HIGH);
};

void shift_register_init()
{

  // Set all the pins of 74HC595 as OUTPUT
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  shift_register_update();
}

void motor_init()
{
  // 默认停止状态
  analogWrite(leftPWM, 0);
  analogWrite(rightPWM, 0);
  // 默认全是低电平 停止状态
  bitClear(values, 7 - MOTOR_LEFT_FORWARD);
  bitClear(values, 7 - MOTOR_LEFT_BACK);
  bitClear(values, 7 - MOTOR_RIGHT_FORWARD);
  bitClear(values, 7 - MOTOR_RIGHT_BACK);
  shift_register_update();
}

void motor_go()
{
  // 左轮前进
  analogWrite(leftPWM, left_speed_level2);
  bitSet(values, 7 - MOTOR_LEFT_FORWARD);
  bitClear(values, 7 - MOTOR_LEFT_BACK);
  // 右轮前进
  analogWrite(rightPWM, right_speed_level2);
  bitSet(values, 7 - MOTOR_RIGHT_FORWARD);
  bitClear(values, 7 - MOTOR_RIGHT_BACK);
}

void motor_back()
{
  analogWrite(leftPWM, left_speed_level2);
  // 左轮后退
  bitClear(values, 7 - MOTOR_LEFT_FORWARD);
  bitSet(values, 7 - MOTOR_LEFT_BACK);
  // 右轮后退;
  analogWrite(rightPWM, right_speed_level2);
  bitClear(values, 7 - MOTOR_RIGHT_FORWARD);
  bitSet(values, 7 - MOTOR_RIGHT_BACK);
}

void motor_turn_left()
{
  // 左轮低速
  analogWrite(leftPWM, left_speed_level1);
  bitSet(values, 7 - MOTOR_LEFT_FORWARD);
  bitClear(values, 7 - MOTOR_LEFT_BACK);
  // 右轮前进
  analogWrite(rightPWM, right_speed_level2);
  bitSet(values, 7 - MOTOR_RIGHT_FORWARD);
  bitClear(values, 7 - MOTOR_RIGHT_BACK);
}

void motor_turn_right()
{
  // 左轮前进
  analogWrite(leftPWM, left_speed_level2);
  bitSet(values, 7 - MOTOR_LEFT_FORWARD);
  bitClear(values, 7 - MOTOR_LEFT_BACK);
  // 右轮低速
  analogWrite(rightPWM, right_speed_level1);
  bitSet(values, 7 - MOTOR_RIGHT_FORWARD);
  bitClear(values, 7 - MOTOR_RIGHT_BACK);
}

void motor_stop()
{
  motor_init();
}

void motor_action(int motor_cmd)
{
  switch (motor_cmd)
  {
  case MOTOR_GO:
    // led_left.on(values);
    // led_right.on(values);
    bitSet(values, 7 - LED_LEFT);
    bitSet(values, 7 - LED_RIGHT);
    motor_go();
    shift_register_update();
    motor_state = motor_cmd;
    break;
  case MOTOR_STOP:
    // led_left.off(values);
    // led_right.off(values);
    bitClear(values, 7 - LED_LEFT);
    bitClear(values, 7 - LED_RIGHT);
    motor_stop();
    shift_register_update();
    motor_state = motor_cmd;
    break;
  case MOTOR_BACK:
    previousMillis = 0;
    bitClear(values, 7 - LED_LEFT);
    bitClear(values, 7 - LED_RIGHT);
    motor_back();
    shift_register_update();
    motor_state = motor_cmd;
    break;
  case MOTOR_LEFT:
    bitSet(values, 7 - LED_LEFT);
    bitClear(values, 7 - LED_RIGHT);
    motor_turn_left();
    shift_register_update();
    motor_state = motor_cmd;
    break;
  case MOTOR_RIGHT:
    bitClear(values, 7 - LED_LEFT);
    bitSet(values, 7 - LED_RIGHT);
    motor_turn_right();
    shift_register_update();
    motor_state = motor_cmd;
    break;
  default:
    break;
  };
};

void ir_init()
{
  // Just to know which program is running on my Arduino
  Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));

  // Start the receiver take LED_BUILTIN pin from the internal boards definition as default feedback LED
  // IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  IrReceiver.begin(IR_RECEIVE_PIN, DISABLE_LED_FEEDBACK); // 释放pin13

  Serial.print(F("Ready to receive IR signals of protocols: "));
  printActiveIRProtocols(&Serial);
  Serial.println(F("at pin " STR(IR_RECEIVE_PIN)));
};

void ir_cmd()
{
  if (IrReceiver.decode())
  {
    // Print a short summary of received data
    IrReceiver.printIRResultShort(&Serial);
    // IrReceiver.printIRSendUsage(&Serial);
    if (IrReceiver.decodedIRData.protocol == UNKNOWN)
    {
      Serial.println(F("Received noise or an unknown (or not yet enabled) protocol"));
      // We have an unknown protocol here, print more info
      IrReceiver.printIRResultRawFormatted(&Serial, true);
    }
    Serial.println();

    //!!!Important!!! Enable receiving of the next value,
    IrReceiver.resume(); // Enable receiving of the next value
    // Finally, check the received data and perform actions according to the received command
    if (IrReceiver.decodedIRData.command == 0x11 || IrReceiver.decodedIRData.command == 0x18 || IrReceiver.decodedIRData.command == 0xCA)
    {
      motor_cmd = MOTOR_GO;
    }
    else if (IrReceiver.decodedIRData.command == 0x14 || IrReceiver.decodedIRData.command == 0x8 || IrReceiver.decodedIRData.command == 0x99)
    {
      motor_cmd = MOTOR_LEFT;
    }
    else if (IrReceiver.decodedIRData.command == 0x16 || IrReceiver.decodedIRData.command == 0x5A || IrReceiver.decodedIRData.command == 0xC1)
    {
      motor_cmd = MOTOR_RIGHT;
    }
    else if (IrReceiver.decodedIRData.command == 0x19 || IrReceiver.decodedIRData.command == 0x52 || IrReceiver.decodedIRData.command == 0xD2)
    {
      motor_cmd = MOTOR_BACK;
    }
    else if (IrReceiver.decodedIRData.command == 0x15 || IrReceiver.decodedIRData.command == 0x1C || IrReceiver.decodedIRData.command == 0xCE)
    {
      motor_cmd = MOTOR_STOP;
    };
  }
  if (motor_cmd != motor_state)
  {
    motor_action(motor_cmd);
  };
}

void softserial_cmd()
{
  // from esp8266 softserial
  String inString = "";
  while (mySerial.available())
  {
    inString += char(mySerial.read());
    Serial.print(inString);
  };

  if (inString.indexOf(GO) != -1)
  {
    motor_cmd = MOTOR_GO;
  }
  else if (inString.indexOf(STOP) != -1)
  {
    motor_cmd = MOTOR_STOP;
  }
  else if (inString.indexOf(BACK) != -1)
  {
    motor_cmd = MOTOR_BACK;
  }
  else if (inString.indexOf(LEFT) != -1)
  {
    motor_cmd = MOTOR_LEFT;
  }
  else if (inString.indexOf(RIGHT) != -1)
  {
    motor_cmd = MOTOR_RIGHT;
  };
  if (motor_cmd != motor_state)
  {
    motor_action(motor_cmd);
  };
}

bool speed_detection()
{
  time = millis();                  // 以毫秒为单位，计算当前时间
  if (abs(time - old_time) >= 1000) // 如果计时时间已达1秒
  {
    detachInterrupt(0); // 关闭外部中断
    detachInterrupt(1);
    // 把每一秒钟编码器码盘计得的脉冲数，换算为当前转速值
    // 转速单位是每分钟多少转，即r/min。这个编码器码盘为20个空洞。
    lv = (float)leftCounter * 60 / 20; // 小车车轮电机转速
    rv = (float)rightCounter * 60 / 20;
    Serial.print("left:");
    Serial.print(lv); // 向上位计算机上传左车轮电机当前转速的高、低字节
    Serial.print("     right:");
    Serial.println(rv); // 向上位计算机上传左车轮电机当前转速的高、低字节
    // 恢复到编码器测速的初始状态,把脉冲计数值清零，以便计算下一秒的脉冲计数
    leftCounter = 0;
    rightCounter = 0;
    old_time = millis();                              // 记录每秒测速时的时间节点
    attachInterrupt(0, RightCount_CallBack, FALLING); // 重新开放外部中断
    attachInterrupt(1, LeftCount_CallBack, FALLING);
    return 1;
  }
  else
    return 0;
}

// 右轮编码器中断服务函数
void RightCount_CallBack()
{
  rightCounter++;
}

// 左轮编码器中断服务函数
void LeftCount_CallBack()
{
  leftCounter++;
}

void distance_detection()
{
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(5);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(ECHO_PIN, INPUT);
  duration = pulseIn(ECHO_PIN, HIGH);

  // Convert the time into a distance
  cm = (duration / 2) / 29.1; // Divide by 29.1 or multiply by 0.0343
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
}

void ultrasonic_init()
{
  //  ultrasonic - Define inputs and outputs
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void led_blink()
{
  unsigned long currentMillis = millis();
  if ((bitRead(values, 7 - LED_LEFT) == 1) && (currentMillis - previousMillis >= 200))
  {
    previousMillis = currentMillis; // Remember the time
    bitClear(values, 7 - LED_LEFT);
    bitClear(values, 7 - LED_RIGHT);
    shift_register_update();
  }
  else if ((bitRead(values, 7 - LED_LEFT) == 0) && (currentMillis - previousMillis >= 200))
  {
    previousMillis = currentMillis; // Remember the time
    bitSet(values, 7 - LED_LEFT);
    bitSet(values, 7 - LED_RIGHT);
    shift_register_update();
  };
}

void setup()
{
  Serial.begin(9600);

  shift_register_init();
  motor_init();
  ir_init();
  ultrasonic_init();

  mySerial.begin(9600);
};

void loop()
{
  bool sd = speed_detection();
  distance_detection();
  if (cm < 30)
  {
    if (motor_state == MOTOR_GO || motor_state == MOTOR_LEFT || motor_state == MOTOR_RIGHT)
    {
      motor_cmd = MOTOR_STOP;
      motor_action(motor_cmd);
    }
  }
  if (motor_state == MOTOR_BACK)
  {
   led_blink();
  };
  ir_cmd();
  softserial_cmd();
}
