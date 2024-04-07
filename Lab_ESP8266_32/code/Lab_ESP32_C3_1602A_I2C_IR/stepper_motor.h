/*  The Simple Dual-Axis Light Tracker  
     ESP32-C3
 */
#ifndef STEPPER_MOTOR_H
#define STEPPER_MOTOR_H

#include <AccelStepper.h>

// Device action code
const int DEV_LEFT = 1;
const int DEV_RIGHT = 2;
const int DEV_UP = 3;
const int DEV_DOWN = 4;
const int DEV_AUTO = 5;

int cur_cmd;

#endif 
