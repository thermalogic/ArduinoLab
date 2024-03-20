/*
  The Simple Dual-Axis Gimbal with 28BYJ-48 Stepper Motors and ULN2003A 
   
   Arduino -> ULN2003A

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

// Include the AccelStepper Library
#include <AccelStepper.h>

// Include the IRremote Library
#include "PinDefinitionsAndMore.h"  // Define macros for input and output pin etc.
#include <IRremote.hpp>
#define DECODE_NEC  // Includes Apple and Onkyo
#define IR_RECEIVE_PIN 2

// IR Remoter: ZTE
#define ACTION_LEFT 0x48
#define ACTION_RIGHT 0x4A
#define ACTION_UP 0x47
#define ACTION_DOWN 0x4B
#define ACTION_MULTI_STEPS_SWITCH 0x49

#define LED_MULTI_STEPS_PIN 12

// Pins entered in sequence IN1-`IN3`-IN2-IN4 for proper step sequence
AccelStepper vertical_stepper(AccelStepper::HALF4WIRE, 8, 10, 9, 11);
AccelStepper horizontal_stepper(AccelStepper::HALF4WIRE, 4, 6, 5, 7);
int multi_steps_on = 0;

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

void multi_steps() {
  // vertical
  turn_left(300);
  turn_right(300);
  
  // horizontal
  turn_up(100);
  turn_down(100);
  }

void setup_irremote() {
  Serial.begin(9600);
  // Just to know which program is running on my Arduino
  Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));

  // Start the receiver and if not 3. parameter specified, take LED_BUILTIN pin from the internal boards definition as default feedback LED
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

  Serial.print(F("Ready to receive IR signals of protocols: "));
  printActiveIRProtocols(&Serial);
  Serial.println(F("at pin " STR(IR_RECEIVE_PIN)));
}

void irremote_control_cmd() {
  if (multi_steps_on == 0) {
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
      case ACTION_MULTI_STEPS_SWITCH:
        multi_steps_on = 1;
        digitalWrite(LED_MULTI_STEPS_PIN, HIGH);
        multi_steps();  // 这个过程如何成为一个线程？
        break;
      default:
        break;
    }
  } else if (multi_steps_on == 1) {
    multi_steps_on = 0;
    digitalWrite(LED_MULTI_STEPS_PIN, LOW);
  };
};

void irremote_control() {
  if (IrReceiver.decode()) {
    // Print a short summary of received data
    IrReceiver.printIRResultShort(&Serial);
    IrReceiver.printIRSendUsage(&Serial);
    if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
      Serial.println(F("Received noise or an unknown (or not yet enabled) protocol"));
      // We have an unknown protocol here, print more info
      IrReceiver.printIRResultRawFormatted(&Serial, true);
    }
    Serial.println();

    IrReceiver.resume();  // Enable receiving of the next value
    irremote_control_cmd();
  };
};

void setup() {
  setup_stepper_motor();
  setup_irremote();
  pinMode(LED_MULTI_STEPS_PIN, OUTPUT);
  digitalWrite(LED_MULTI_STEPS_PIN, LOW);
  multi_steps_on = 0;
  delay(1000);
};

void loop() {
  irremote_control();
}
