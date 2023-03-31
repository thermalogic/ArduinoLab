#include "PinDefinitionsAndMore.h"  // Define macros for input and output pin etc.
#include <IRremote.hpp>
#include <SoftwareSerial.h>

#define DECODE_NEC  // Includes Apple and Onkyo
#define IR_RECEIVE_PIN 7

int latchPin = 3;  // Latch pin of 74HC595 is connected to Digital pin 3
int clockPin = 4;  // Clock pin of 74HC595 is connected to Digital pin 4
int dataPin = 2;   // Data pin of 74HC595 is connected to Digital pin 2

byte values = 0;  // Variable to hold the pattern of which LEDs are currently turned on or off

// 74hc595
#define MOTOR_LEFT_FORWARD 4
#define MOTOR_LEFT_BACK 3
#define MOTOR_RIGHT_FORWARD 2
#define MOTOR_RIGHT_BACK 1
#define LED_LEFT 5
#define LED_RIGHT 6
//arduino
#define leftPWM 6
#define rightPWM 5

#define MOTOR_GO 0
#define MOTOR_BACK 1
#define MOTOR_STOP 2
#define MOTOR_LEFT 3
#define MOTOR_RIGHT 4

int speed_level1 = 0;  // 转向时用，转速差，转向
int speed_level2 = 200;  // 太低驱动不了，调试后200，比较合适
int speed_level3 = 255;

int motor_state = MOTOR_STOP;
int motor_cmd = MOTOR_STOP;

long previousMillis;

String GO = "G";
String STOP = "S";
String BACK = "B";
String LEFT = "L";
String RIGHT = "R";
#define SS_RX 10  
#define SS_TX 11
SoftwareSerial mySerial(SS_RX, SS_TX);

void updateShiftRegister() {
  //
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, values);
  digitalWrite(latchPin, HIGH);
};

void motor_init() {
  // 默认停止状态
  analogWrite(leftPWM, 0);
  analogWrite(rightPWM, 0);
  // 默认全是低电平 停止状态
  bitClear(values, 7 - MOTOR_LEFT_FORWARD);
  bitClear(values, 7 - MOTOR_LEFT_BACK);
  bitClear(values, 7 - MOTOR_RIGHT_FORWARD);
  bitClear(values, 7 - MOTOR_RIGHT_BACK);
  updateShiftRegister();
}

void motor_go() {
  // 左轮前进
  analogWrite(leftPWM, speed_level2);
  bitSet(values, 7 - MOTOR_LEFT_FORWARD);
  bitClear(values, 7 - MOTOR_LEFT_BACK);
  // 右轮前进
  analogWrite(rightPWM, speed_level2);
  bitSet(values, 7 - MOTOR_RIGHT_FORWARD);
  bitClear(values, 7 - MOTOR_RIGHT_BACK);
}

void motor_back() {
  analogWrite(leftPWM, speed_level2);
  // 左轮后退
  bitClear(values, 7 - MOTOR_LEFT_FORWARD);
  bitSet(values, 7 - MOTOR_LEFT_BACK);
  // 右轮后退;
  analogWrite(rightPWM, speed_level2);
  bitClear(values, 7 - MOTOR_RIGHT_FORWARD);
  bitSet(values, 7 - MOTOR_RIGHT_BACK);
}

void motor_turn_left() {
  // 左轮低速
  analogWrite(leftPWM, speed_level1);
  bitSet(values, 7 - MOTOR_LEFT_FORWARD);
  bitClear(values, 7 - MOTOR_LEFT_BACK);
  // 右轮前进
  analogWrite(rightPWM, speed_level2);
  bitSet(values, 7 - MOTOR_RIGHT_FORWARD);
  bitClear(values, 7 - MOTOR_RIGHT_BACK);
}

void motor_turn_right() {
  // 左轮前进
  analogWrite(leftPWM, speed_level2);
  bitSet(values, 7 - MOTOR_LEFT_FORWARD);
  bitClear(values, 7 - MOTOR_LEFT_BACK);
  // 右轮低速
  analogWrite(rightPWM, speed_level1);
  bitSet(values, 7 - MOTOR_RIGHT_FORWARD);
  bitClear(values, 7 - MOTOR_RIGHT_BACK);
}

void motor_stop() {
  motor_init();
}


void motor_action(int motor_cmd) {
  switch (motor_cmd) {
    case MOTOR_GO:
      //led_left.on(values);
      //led_right.on(values);
      bitSet(values, 7 - LED_LEFT);
      bitSet(values, 7 - LED_RIGHT);
      motor_go();
      updateShiftRegister();
      motor_state = motor_cmd;
      break;
    case MOTOR_STOP:
      //led_left.off(values);
      //led_right.off(values);
      bitClear(values, 7 - LED_LEFT);
      bitClear(values, 7 - LED_RIGHT);
      motor_stop();
      updateShiftRegister();
      motor_state = motor_cmd;
      break;
    case MOTOR_BACK:
      previousMillis = 0;
      bitClear(values, 7 - LED_LEFT);
      bitClear(values, 7 - LED_RIGHT);
      motor_back();
      updateShiftRegister();
      motor_state = motor_cmd;
      break;
    case MOTOR_LEFT:
      bitSet(values, 7 - LED_LEFT);
      bitClear(values, 7 - LED_RIGHT);
      motor_turn_left();
      updateShiftRegister();
      motor_state = motor_cmd;
      break;
    case MOTOR_RIGHT:
      bitClear(values, 7 - LED_LEFT);
      bitSet(values, 7 - LED_RIGHT);
      motor_turn_right();
      updateShiftRegister();
      motor_state = motor_cmd;
      break;
    default:
      break;
  };
};

void ir_init() {
  // Just to know which program is running on my Arduino
  Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));

  // Start the receiver take LED_BUILTIN pin from the internal boards definition as default feedback LED
  // IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  IrReceiver.begin(IR_RECEIVE_PIN, DISABLE_LED_FEEDBACK);  //释放pin13

  Serial.print(F("Ready to receive IR signals of protocols: "));
  printActiveIRProtocols(&Serial);
  Serial.println(F("at pin " STR(IR_RECEIVE_PIN)));
};

void ir_cmd() {
  if (IrReceiver.decode()) {
    // Print a short summary of received data
    IrReceiver.printIRResultShort(&Serial);
    //IrReceiver.printIRSendUsage(&Serial);
    if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
      Serial.println(F("Received noise or an unknown (or not yet enabled) protocol"));
      // We have an unknown protocol here, print more info
      IrReceiver.printIRResultRawFormatted(&Serial, true);
    }
    Serial.println();

    //!!!Important!!! Enable receiving of the next value,
    IrReceiver.resume();  // Enable receiving of the next value
    // Finally, check the received data and perform actions according to the received command
    if (IrReceiver.decodedIRData.command == 0x11 || IrReceiver.decodedIRData.command == 0x18 || IrReceiver.decodedIRData.command == 0xCA) {
      // forward - 2
      motor_cmd = MOTOR_GO;
      // }
    } else if (IrReceiver.decodedIRData.command == 0x14 || IrReceiver.decodedIRData.command == 0x8 || IrReceiver.decodedIRData.command == 0x99) {
      // Left - 4
      motor_cmd = MOTOR_LEFT;
    } else if (IrReceiver.decodedIRData.command == 0x16 || IrReceiver.decodedIRData.command == 0x5A || IrReceiver.decodedIRData.command == 0xC1) {
      // right - 6
      motor_cmd = MOTOR_RIGHT;
    } else if (IrReceiver.decodedIRData.command == 0x19 || IrReceiver.decodedIRData.command == 0x52 || IrReceiver.decodedIRData.command == 0xD2) {
      // back - 8
      motor_cmd = MOTOR_BACK;
    } else if (IrReceiver.decodedIRData.command == 0x15 || IrReceiver.decodedIRData.command == 0x1C || IrReceiver.decodedIRData.command == 0xCE) {
      // stop - 5
      motor_cmd = MOTOR_STOP;
    };
  }
  if (motor_cmd != motor_state) {
    motor_action(motor_cmd);
  };
}

void softserial_cmd(){
// from esp8266 serial
  String inString = "";
  while (mySerial.available()) {
    inString += char(mySerial.read());
    Serial.print(inString);
  };

  if (inString.indexOf(GO) != -1) {
    motor_cmd = MOTOR_GO;
  } else if (inString.indexOf(STOP) != -1) {
    motor_cmd = MOTOR_STOP;
  } else if (inString.indexOf(BACK) != -1) {
    motor_cmd = MOTOR_BACK;
  } else if (inString.indexOf(LEFT) != -1) {
    motor_cmd = MOTOR_LEFT;
  } else if (inString.indexOf(RIGHT) != -1) {
    motor_cmd = MOTOR_RIGHT;
  };
  if (motor_cmd != motor_state) {
    motor_action(motor_cmd);
  };
}

void setup() {
  Serial.begin(9600);
  // Set all the pins of 74HC595 as OUTPUT
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  updateShiftRegister();
  motor_init();
  ir_init();
  mySerial.begin(9600);
};

void loop() {
  
  if (motor_state == MOTOR_BACK) {
    unsigned long currentMillis = millis();
    if ((bitRead(values, 7 - LED_LEFT) == 1) && (currentMillis - previousMillis >= 200)) {
      previousMillis = currentMillis;  // Remember the time
      bitClear(values, 7 - LED_LEFT);
      bitClear(values, 7 - LED_RIGHT);
        updateShiftRegister();
    } else if ((bitRead(values, 7 - LED_LEFT) == 0) && (currentMillis - previousMillis >= 200)) {
      previousMillis = currentMillis;  // Remember the time
      bitSet(values, 7 - LED_LEFT);
      bitSet(values, 7 - LED_RIGHT);
      updateShiftRegister();
    };
  
  };
  ir_cmd();
  softserial_cmd();
}
