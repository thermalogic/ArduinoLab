/*
   第2轴有限幅度的上小杨姣调整
   
   28byj-48 Stepper Motor and  Solar tracing


   Arduino pin: ULN2003A IN pin out pin color code on the byj stepper
    * 8 in1 
    * 9 in2 
    * 10 in3
    * 11 in4

    AccelStepper byj(AccelStepper::HALF4WIRE, 8, 10, 9, 11); // byj - pins 2 and 3 swapped !!!
*/

// Include the AccelStepper Library
#include <AccelStepper.h>

// Creates an instance
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
AccelStepper stepper(AccelStepper::HALF4WIRE, 8, 10, 9, 11);

const int max_steps=800;
int currentPosition;

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
  delay(2000);
}

void turn_up(int steps) {
  currentPosition = stepper.currentPosition();
    Serial.print("---currentPosition:");
  Serial.println(currentPosition);
  if (abs(currentPosition)<max_steps)
  {  stepper.move(-steps);   // relative position 
     stepper.runToPosition();
  }
  currentPosition = stepper.currentPosition();
  if (abs(currentPosition)>max_steps)
   { if (currentPosition<0)  stepper.moveTo(-max_steps);   // relative position 
     if (currentPosition>0)  stepper.moveTo(max_steps);   // relative position 
     stepper.runToPosition();
  }
}

void turn_down(int steps) {
  currentPosition = stepper.currentPosition();
  if (abs(currentPosition)<max_steps)
  {  stepper.move(steps);   // relative position 
     stepper.runToPosition();
  };
  currentPosition = stepper.currentPosition();
  if (abs(currentPosition)>max_steps)
   { if (currentPosition<0)  stepper.moveTo(-max_steps);   // relative position 
     if (currentPosition>0)  stepper.moveTo(max_steps);   // relative position 
     stepper.runToPosition();
  }
}

void loop() {
     for(int i=0;i<20;i++)
     {
      turn_up(50);
      delay(100);
     }
    stepper.setCurrentPosition(0);  
    for(int i=0;i<20;i++)
    {
      turn_down(50);
      delay(100);
    }
}
