/*  The Simple Dual-Axis Light Tracker   */

#include <AccelStepper.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
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

const int left_photoresistor = A0;
const int right_photoresistor = A1;
const int up_photoresistor = A2;
const int down_photoresistor = A3;

//variable to hold sensor value
int left_sensor;
int right_sensor;
int diff_left_right_sensor;
int max_diff_left_right_sensor = 100;

//variable to hold sensor value
int up_sensor;
int down_sensor;
int diff_up_down_sensor;
int max_diff_up_down_sensor = 100;
int down_sensor_add = 300;

int left_right_steps = 50;
int up_down_steps = 30;
int manual_steps = 50;

LiquidCrystal_I2C lcd(0x27, 16, 2);  

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
  horizontal_stepper.move(-steps);
  horizontal_stepper.runToPosition();
}

void turn_down(int steps) {
  horizontal_stepper.move(steps);
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
      turn_left(manual_steps);
      break;
    case ACTION_RIGHT:
      turn_right(manual_steps);
      break;
    case ACTION_UP:
      turn_up(manual_steps);
      break;
    case ACTION_DOWN:
      turn_down(manual_steps);
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
  left_sensor = analogRead(left_photoresistor);
  right_sensor = analogRead(right_photoresistor);
  diff_left_right_sensor = left_sensor - right_sensor;

  up_sensor = analogRead(up_photoresistor);
  down_sensor = analogRead(down_photoresistor) + down_sensor_add;
  diff_up_down_sensor = up_sensor - down_sensor;
}

void tracking_light_left_right() {
  if (auto_on == 1) {
    if (abs(diff_left_right_sensor) >= max_diff_left_right_sensor) {
      if (left_sensor > right_sensor) {
        turn_left(left_right_steps);
      };
      if (right_sensor > left_sensor) {
        turn_right(left_right_steps);
      };
    }
  }
  left_sensor = analogRead(left_photoresistor);
  right_sensor = analogRead(right_photoresistor);
  diff_left_right_sensor = left_sensor - right_sensor;
}

void tracking_light_up_down() {
  if (auto_on == 1) {
    if (abs(diff_up_down_sensor) >= max_diff_up_down_sensor) {
      if (up_sensor > down_sensor) {
        turn_up(up_down_steps);
      };
      if (down_sensor > up_sensor) {
        turn_down(up_down_steps);
      };
    }
  }
  up_sensor = analogRead(up_photoresistor);
  down_sensor = analogRead(down_photoresistor) + down_sensor_add;
  diff_up_down_sensor = up_sensor - down_sensor;
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
  lcd.print(left_sensor);
  lcd.print(" U ");
  lcd.print(up_sensor);
  if (auto_on == 1) {
    lcd.print(" AUTO");
  } else {
    lcd.print("  IR ");
  };
  lcd.setCursor(0, 1);
  lcd.print("R ");
  lcd.print(right_sensor);
  lcd.print(" D ");
  lcd.print(down_sensor);
  delay(500);
}
