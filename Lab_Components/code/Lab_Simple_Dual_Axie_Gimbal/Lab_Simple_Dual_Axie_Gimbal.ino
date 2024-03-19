/*
  The Simple Dual-Axis Gimbal with 28BYJ-48 Stepper Motors and ULN2003A 
   
   Arduino -> ULN2003A: 

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

// Pins entered in sequence IN1-`IN3`-IN2-IN4 for proper step sequence
AccelStepper vertical_stepper(AccelStepper::HALF4WIRE, 8, 10, 9, 11);
AccelStepper horizontal_stepper(AccelStepper::HALF4WIRE, 4, 6, 5, 7);


void turn_left(int steps) {
  vertical_stepper.move(-steps);  // relative position
  vertical_stepper.runToPosition();
}

void turn_right(int steps) {
  vertical_stepper.move(steps);
  vertical_stepper.runToPosition();
}

void turn_up(int steps) {
    horizontal_stepper.move(steps);  // relative position
    horizontal_stepper.runToPosition();
  }


void turn_down(int steps) {
    horizontal_stepper.move(-steps);  // relative position
    horizontal_stepper.runToPosition();
}

void setup() {
  Serial.begin(9600);

  vertical_stepper.setMaxSpeed(1000.0);
  vertical_stepper.setAcceleration(50.0);
  vertical_stepper.setSpeed(500);

  horizontal_stepper.setMaxSpeed(1000.0);
  horizontal_stepper.setAcceleration(50.0);
  horizontal_stepper.setSpeed(500);
  delay(1000);
}


void loop() {
  // vertical
  turn_left(300);
  delay(1000);
  turn_right(300);
  delay(1000);

  // horizontal
  turn_up(100);
  delay(1000);
  turn_down(100);
  delay(1000);
}
