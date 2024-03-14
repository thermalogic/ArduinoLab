/*
   Stepper Motor and  Solar tracing
*/

// Include the AccelStepper Library
#include <AccelStepper.h>

// Creates an instance
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
AccelStepper stepper(AccelStepper::HALF4WIRE, 8, 10, 9, 11);

void setup()
{  
  stepper.setMaxSpeed(150);
  stepper.setAcceleration(100);
}
 
void loop()
{    
  stepper.moveTo(500);
  while (stepper.currentPosition() != 300) // Full speed up to 300
    stepper.run();
  stepper.stop(); // Stop as fast as possible: sets new target
  stepper.runToPosition(); 
  // Now stopped after quickstop
 
  // Now go backwards
  stepper.moveTo(-500);
  while (stepper.currentPosition() != 0) // Full speed basck to 0
    stepper.run();
  stepper.stop(); // Stop as fast as possible: sets new target
  stepper.runToPosition(); 
  // Now stopped after quickstop
 
}
