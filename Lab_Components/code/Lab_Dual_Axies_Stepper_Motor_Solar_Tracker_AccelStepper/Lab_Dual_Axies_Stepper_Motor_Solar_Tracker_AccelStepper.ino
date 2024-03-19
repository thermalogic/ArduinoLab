/*
   Dual-Axis Gimbal with 28BYJ-48 Stepper Motors with ULN2003A 
   
   Arduino -> ULN2003A pin: 

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

// Creates an instance

// Pins entered in sequence IN1-`IN3`-IN2-IN4 for proper step sequence
// vertical stepper motor
AccelStepper vertical_stepper(AccelStepper::HALF4WIRE, 8, 10, 9, 11);
AccelStepper horizontal_stepper(AccelStepper::HALF4WIRE, 4, 6, 5, 7);


const int max_steps = 400;
int currentPosition;
int horizontal_currentPosition;

void turn_left(int steps) {
  vertical_stepper.move(-steps);  // relative position
  vertical_stepper.runToPosition();
}

void turn_right(int steps) {
  vertical_stepper.move(steps);
  vertical_stepper.runToPosition();
}

void turn_up(int steps) {
  horizontal_currentPosition = horizontal_stepper.currentPosition();
  Serial.print("---horizontal currentPosition:");
  Serial.println(horizontal_currentPosition);
  if (abs(horizontal_currentPosition) < max_steps) {
    horizontal_stepper.move(steps);  // relative position
    horizontal_stepper.runToPosition();
  }
  horizontal_currentPosition = horizontal_stepper.currentPosition();
  if (abs(horizontal_currentPosition) > max_steps) {
    if (horizontal_currentPosition < 0) horizontal_stepper.moveTo(-max_steps);  // relative position
    if (horizontal_currentPosition > 0) horizontal_stepper.moveTo(max_steps);   // relative position
    horizontal_stepper.runToPosition();
  }
}

void turn_down(int steps) {
  horizontal_currentPosition = horizontal_stepper.currentPosition();
  Serial.print("---horizontal  currentPosition:");
  Serial.println(horizontal_currentPosition);

  if (abs(horizontal_currentPosition) < max_steps) {
    horizontal_stepper.move(-steps);  // relative position
    horizontal_stepper.runToPosition();
  };
  horizontal_currentPosition = horizontal_stepper.currentPosition();
  if (abs(horizontal_currentPosition) > max_steps) {
    if (horizontal_currentPosition < 0) horizontal_stepper.moveTo(-max_steps);  // relative position
    if (horizontal_currentPosition > 0) horizontal_stepper.moveTo(max_steps);   // relative position
    horizontal_stepper.runToPosition();
  }
}

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  // set the maximum speed, acceleration factor,
  // initial speed and the target position
  vertical_stepper.setMaxSpeed(1000.0);
  vertical_stepper.setAcceleration(50.0);
  vertical_stepper.setSpeed(500);

  currentPosition = vertical_stepper.currentPosition();
  Serial.print("---currentPosition:");
  Serial.println(currentPosition);


  horizontal_stepper.setMaxSpeed(1000.0);
  horizontal_stepper.setAcceleration(50.0);
  horizontal_stepper.setSpeed(500);

  horizontal_currentPosition = horizontal_stepper.currentPosition();
  Serial.print("---horizontal currentPosition:");
  Serial.println(horizontal_currentPosition);
  delay(1000);
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


void loop() {
}
