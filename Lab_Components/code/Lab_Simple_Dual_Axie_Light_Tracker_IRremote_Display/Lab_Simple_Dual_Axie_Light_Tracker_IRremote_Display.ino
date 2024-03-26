/*
  The Simple Dual-Axis Light Tracker
    - 28BYJ-48 Stepper Motors and ULN2003A 
    - IR remote control   
    - 1602A I2C Display
    - Photoresistor
  
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

#include <AccelStepper.h>

const int Left_PhotoResistor = A0;
const int Right_PhotoResistor = A1;
const int Up_PhotoResistor = A2;
const int Down_PhotoResistor = A3;

//variable to hold sensor value
int Left_sensorValue;
int Right_sensorValue;
int diff_left_right_sensorValue;

//variable to hold sensor value
int Up_sensorValue;
int Down_sensorValue;
int diff_up_down_sensorValue;
int Down_sensorValue_add = 300;

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);  //配置LCD地址及行列


#include "PinDefinitionsAndMore.h"
#include <IRremote.hpp>
#define DECODE_NEC
#define IR_RECEIVE_PIN 2

// IR Remoter: ZTE
#define ACTION_LEFT 0x48
#define ACTION_RIGHT 0x4A
#define ACTION_UP 0x47
#define ACTION_DOWN 0x4B
#define AUTO_ON 0x49
int auto_on = 0;

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
      turn_left(50);
      break;
    case ACTION_RIGHT:
      turn_right(50);
      break;
    case ACTION_UP:
      turn_up(50);
      break;
    case ACTION_DOWN:
      turn_down(50);
      break;
    case AUTO_ON:
      if (auto_on == 0) {
        auto_on = 1;
      } else {
        auto_on = 0;
      }
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

void init_photoresistor() {
  Left_sensorValue = analogRead(Left_PhotoResistor);
  Right_sensorValue = analogRead(Right_PhotoResistor);
  diff_left_right_sensorValue = Left_sensorValue - Right_sensorValue;

  Up_sensorValue = analogRead(Up_PhotoResistor);
  Down_sensorValue = analogRead(Down_PhotoResistor) + Down_sensorValue_add;
  diff_up_down_sensorValue = Up_sensorValue - Down_sensorValue;
}

void tracking_light_left_right() {
  if (auto_on == 1) {

    if (abs(diff_left_right_sensorValue) >= 50) {
      if (Left_sensorValue > Right_sensorValue) {
        Serial.println("Turning Left: ");
        turn_left(100);
      };
      if (Right_sensorValue > Left_sensorValue) {
        Serial.println("Turning Right: ");
        turn_right(100);
      };
    }
  }
  Left_sensorValue = analogRead(Left_PhotoResistor);
  Right_sensorValue = analogRead(Right_PhotoResistor);
  diff_left_right_sensorValue = Left_sensorValue - Right_sensorValue;
  Serial.println(" ");
  Serial.print("Left sensorValue: ");
  Serial.println(Left_sensorValue);
  Serial.print("Right sensorValue: ");
  Serial.println(Right_sensorValue);
  Serial.print("diff sensorValue: ");
  Serial.println(diff_left_right_sensorValue);
}

void tracking_light_up_down() {
  if (auto_on == 1) {

    if (abs(diff_up_down_sensorValue) >= 50) {
      if (Up_sensorValue > Down_sensorValue) {
        Serial.println("Turning Up: ");
        turn_up(30);
      };
      if (Down_sensorValue > Up_sensorValue) {
        Serial.println("Turning Down: ");
        turn_down(30);
      };
    }
  }
  Up_sensorValue = analogRead(Up_PhotoResistor);
  Down_sensorValue = analogRead(Down_PhotoResistor) + Down_sensorValue_add;
  diff_up_down_sensorValue = Up_sensorValue - Down_sensorValue;
  Serial.println(" ");
  Serial.print("Up sensorValue: ");
  Serial.println(Up_sensorValue);
  Serial.print("Down sensorValue: ");
  Serial.println(Down_sensorValue);
  diff_up_down_sensorValue = Up_sensorValue - Down_sensorValue;
  Serial.print("diff up down sensorValue: ");
  Serial.println(diff_up_down_sensorValue);
}

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Dual-Axis Gimbal");
  lcd.setCursor(0, 1);
  lcd.print(" Tracking Light");

  setup_stepper_motor();
  setup_irremote();
  init_photoresistor();
  delay(2000);
  lcd.clear();
};

void loop() {
  irremote_control();
  tracking_light_left_right();
  tracking_light_up_down();
 
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("L ");
  lcd.print(Left_sensorValue);
  lcd.print(" U ");
  lcd.print(Up_sensorValue);
  if (auto_on == 1) {
    lcd.print(" AUTO");
  } else {
    lcd.print("  IR ");
  };
  lcd.setCursor(0, 1);
  lcd.print("R ");
  lcd.print(Right_sensorValue);
  lcd.print(" D ");
  lcd.print(Down_sensorValue);
  delay(500);
}
