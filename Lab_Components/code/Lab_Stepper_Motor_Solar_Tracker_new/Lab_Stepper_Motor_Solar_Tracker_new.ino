/*
  Stepper Motor and  Solar tracing
int in1Pin = 8;
int in2Pin = 9;
int in3Pin = 10;
int in4Pin = 11;
*/

// Include the AccelStepper Library
#include <AccelStepper.h>

// Define step constant
#define FULLSTEP 4

// Creates an instance
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
AccelStepper myStepper(FULLSTEP, 8, 9, 10, 11);

int currentPosition;
const int Left_PhotoResistor = A0;
const int Right_PhotoResistor = A1;

//variable to hold sensor value
int Left_sensorValue;
int Right_sensorValue;
int diff_sensorValue;


void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  // set the maximum speed, acceleration factor,
  // initial speed and the target position
  myStepper.setMaxSpeed(1000.0);
  myStepper.setAcceleration(50.0);
  myStepper.setSpeed(200);

  currentPosition =  myStepper.currentPosition();
  Serial.print("currentPosition:");
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
  currentPosition =  myStepper.currentPosition();
  myStepper.moveTo(currentPosition-steps);
  myStepper.runToPosition();
 }

void turn_right(int steps) {
   currentPosition =  myStepper.currentPosition();
   myStepper.moveTo(currentPosition-steps);
   myStepper.runToPosition();
 }

void loop() {
  if (Left_sensorValue - 30 > Right_sensorValue) {
    Serial.println("Turning Left: ");
    turn_left(10);
    
  }
  if (Right_sensorValue - 30 > Left_sensorValue) {
    Serial.println("Turning Right: ");
    turn_right(10);
  };
  Left_sensorValue = analogRead(Left_PhotoResistor);
  Right_sensorValue = analogRead(Right_PhotoResistor);
  Serial.print("Left sensorValue: ");
  Serial.println(Left_sensorValue);
  Serial.print("Right sensorValue: ");
  Serial.println(Right_sensorValue);
  diff_sensorValue = Left_sensorValue - Right_sensorValue;
  Serial.print("diff sensorValue: ");
  Serial.println(diff_sensorValue);
  currentPosition = myStepper.currentPosition();
  Serial.print("---currentPosition:");
  Serial.println(currentPosition);
  
  delay(2000);
}
