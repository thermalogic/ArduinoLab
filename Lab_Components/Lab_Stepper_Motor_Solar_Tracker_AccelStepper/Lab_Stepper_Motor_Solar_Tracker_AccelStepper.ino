/*
   28byj-48 Stepper Motor and  Solar tracing
   Arduino pin: ULN2003A IN pin out pin color code on the byj stepper
    * 8 in4 
    * 9 in3 
    * 10 in2
    * 11 in1

    AccelStepper byj(AccelStepper::HALF4WIRE, 8, 10, 9, 11); // byj - pins 2 and 3 swapped !!!
*/

// Include the AccelStepper Library
#include <AccelStepper.h>

// Creates an instance
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
AccelStepper stepper(AccelStepper::HALF4WIRE, 8, 10, 9, 11);

int currentPosition;
const int Left_PhotoResistor = A0;
const int Right_PhotoResistor = A1;

//variable to hold sensor value
int Left_sensorValue;
int Right_sensorValue;
int diff_sensorValue;
int turn_steps=50;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  // set the maximum speed, acceleration factor,
  // initial speed and the target position
  stepper.setMaxSpeed(1000.0);
  stepper.setAcceleration(50.0);
  stepper.setSpeed(200);

  currentPosition = stepper.currentPosition();
  Serial.print("---currentPosition:");
  Serial.println(currentPosition);

  Left_sensorValue = analogRead(Left_PhotoResistor);
  Right_sensorValue = analogRead(Right_PhotoResistor);

  Serial.print("Left sensorValue: ");
  Serial.println(Left_sensorValue);
  Serial.print("Right sensorValue: ");
  Serial.println(Right_sensorValue);
  diff_sensorValue = Left_sensorValue - Right_sensorValue;
  Serial.print("diff sensorValue: ");
  Serial.println(diff_sensorValue);
  delay(2000);
}

void turn_left(int steps) {
  stepper.move(-steps);   // relative position 
  stepper.runToPosition();
}

void turn_right(int steps) {
  stepper.move(steps);
  stepper.runToPosition();
}

void loop() {
  if (abs(diff_sensorValue) >= 30) {
    if (Left_sensorValue > Right_sensorValue) {
      Serial.println("Turning Left: ");
      turn_left(100);
    };
    if (Right_sensorValue > Left_sensorValue) {
      Serial.println("Turning Right: ");
      turn_right(100);
    };
  }
  Left_sensorValue = analogRead(Left_PhotoResistor);
  Right_sensorValue = analogRead(Right_PhotoResistor);
  Serial.println(" ");
  Serial.print("Left sensorValue: ");
  Serial.println(Left_sensorValue);
  Serial.print("Right sensorValue: ");
  Serial.println(Right_sensorValue);
  diff_sensorValue = Left_sensorValue - Right_sensorValue;
  Serial.print("diff sensorValue: ");
  Serial.println(diff_sensorValue);
  currentPosition = stepper.currentPosition();
  Serial.print("---currentPosition:");
  Serial.println(currentPosition);
  delay(500);
}
