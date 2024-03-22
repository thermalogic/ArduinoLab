/*
  The Simple Dual-Axis Gimbal with 28BYJ-48 Stepper Motors and ULN2003A 
   -  IR remote control   
   - 1602A I2C Display
  
   vertical stepper motor
    * 8 in1 
    * 9 in2 
    * 10 in3
    * 11 in4
  
  horizontal_stepper
    * 4 in1 
    * 5 in2 
    * 6 in3
    * 7 in4
*/


#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  //配置LCD地址及行列

#include <AccelStepper.h>

#include "PinDefinitionsAndMore.h"  
#include <IRremote.hpp>
#define DECODE_NEC  
#define IR_RECEIVE_PIN 2

// IR Remoter: ZTE
#define ACTION_LEFT 0x48
#define ACTION_RIGHT 0x4A
#define ACTION_UP 0x47
#define ACTION_DOWN 0x4B

#define LED_MOVING_PIN 12

// Pins entered in sequence IN1-`IN3`-IN2-IN4 for proper step sequence
AccelStepper vertical_stepper(AccelStepper::HALF4WIRE, 8, 10, 9, 11);
AccelStepper horizontal_stepper(AccelStepper::HALF4WIRE, 4, 6, 5, 7);

void setup_stepper_motor() {
  vertical_stepper.setMaxSpeed(1000.0);
  vertical_stepper.setAcceleration(50.0);
  vertical_stepper.setSpeed(500);

  horizontal_stepper.setMaxSpeed(1000.0);
  horizontal_stepper.setAcceleration(50.0);
  horizontal_stepper.setSpeed(500);
}

void turn_left(int steps) {
  vertical_stepper.move(-steps);  // relative position
  vertical_stepper.runToPosition();
}

void turn_right(int steps) {
  vertical_stepper.move(steps);
  vertical_stepper.runToPosition();
}

void turn_up(int steps) {
  horizontal_stepper.move(-steps);  // relative position
  horizontal_stepper.runToPosition();
}

void turn_down(int steps) {
  horizontal_stepper.move(steps);  // relative position
  horizontal_stepper.runToPosition();
}

void setup_irremote() {
  Serial.begin(9600);
  Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));

  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

  Serial.print(F("Ready to receive IR signals of protocols: "));
  printActiveIRProtocols(&Serial);
  Serial.println(F("at pin " STR(IR_RECEIVE_PIN)));
}

void irremote_control_cmd() {
  switch (IrReceiver.decodedIRData.command) {
    case ACTION_LEFT:
      digitalWrite(LED_MOVING_PIN, HIGH);
      turn_left(50);
      digitalWrite(LED_MOVING_PIN, LOW);
      break;
    case ACTION_RIGHT:
      digitalWrite(LED_MOVING_PIN, HIGH);
      turn_right(50);
      digitalWrite(LED_MOVING_PIN, LOW);
      break;
    case ACTION_UP:
      digitalWrite(LED_MOVING_PIN, HIGH);
      turn_up(50);
      digitalWrite(LED_MOVING_PIN, LOW);
      break;
    case ACTION_DOWN:
      digitalWrite(LED_MOVING_PIN, HIGH);
      turn_down(50);
      break;
      digitalWrite(LED_MOVING_PIN, LOW);
      break;
    default:
      break;
  };
};

void irremote_control() {
  if (IrReceiver.decode()) {
    IrReceiver.printIRResultShort(&Serial);
    IrReceiver.printIRSendUsage(&Serial);
    if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
      Serial.println(F("Received noise or an unknown (or not yet enabled) protocol"));
      IrReceiver.printIRResultRawFormatted(&Serial, true);
    }
    Serial.println();
    IrReceiver.resume();  
    irremote_control_cmd();
  };
};

void setup() {
   lcd.init(); //初始化LCD
   lcd.backlight(); //打开背光
   lcd.setCursor(0,0);//设置显示位置
   lcd.print("Dual-Axis Gimbal");
   lcd.setCursor(0,1);//设置显示位置
   lcd.print(" Tracking Light");
  
  setup_stepper_motor();
  setup_irremote();
  pinMode(LED_MOVING_PIN, OUTPUT);
  digitalWrite(LED_MOVING_PIN, LOW);
};

void loop() {
  irremote_control();
}
