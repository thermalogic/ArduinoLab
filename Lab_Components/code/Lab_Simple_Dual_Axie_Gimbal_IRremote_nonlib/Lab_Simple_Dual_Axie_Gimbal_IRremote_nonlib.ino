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
#define ACTION_STOP 0x49


#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4
#define STOP 0


#define LED_STEPPER_MOTOR_ON 12

void setup_stepper_motor() {
  //vertical_stepper.
  for (int i = 8; i < 12; i++) {
    pinMode(i, OUTPUT);
  }
  //  horizontal_stepper
  for (int i = 4; i < 8; i++) {
    pinMode(i, OUTPUT);
  }
}

void vertical_stepper_clockwise(int num) {
  for (int count = 0; count < num; count++) {
    if (IrReceiver.decodedIRData.command!=ACTION_STOP)
    {
        for (int i = 8; i < 12; i++) {
          digitalWrite(i, HIGH);
          delay(3);
          digitalWrite(i, LOW);
        }
      }
    else { break; }
  }
}

void vertical_stepper_anticlockwise(int num) {
  for (int count = 0; count < num; count++) {
    if (IrReceiver.decodedIRData.command!=ACTION_STOP)
    {
        for (int i = 11; i > 7; i--) {
          digitalWrite(i, HIGH);
          delay(3);
          digitalWrite(i, LOW);
        }
      }
    else { break; }
  }
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

void irremote_cmd() {
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
    switch (IrReceiver.decodedIRData.command) {
      case ACTION_LEFT:
       digitalWrite(LED_STEPPER_MOTOR_ON, HIGH);
       vertical_stepper_anticlockwise(1000);
       digitalWrite(LED_STEPPER_MOTOR_ON, LOW);
       break;
      case ACTION_RIGHT:
      default:
       digitalWrite(LED_STEPPER_MOTOR_ON, HIGH);
       vertical_stepper_clockwise(1000);
       digitalWrite(LED_STEPPER_MOTOR_ON, LOW);
       break;
    }
  };
};

void setup() {
  setup_stepper_motor();
  setup_irremote();
  pinMode(LED_STEPPER_MOTOR_ON, OUTPUT);
  digitalWrite(LED_STEPPER_MOTOR_ON, LOW);
 };

void loop() {
  irremote_cmd();
}
