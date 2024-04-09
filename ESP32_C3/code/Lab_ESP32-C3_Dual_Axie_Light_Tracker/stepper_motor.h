/*  The Simple Dual-Axis Light Tracker  
     ESP32-C3
 */
#ifndef STEPPER_MOTOR_H
#define STEPPER_MOTOR_H

#include <AccelStepper.h>

int left_right_steps = 50;
int up_down_steps = 30;
int manual_steps = 50;

// Device action code
const int DEV_LEFT = 1;
const int DEV_RIGHT = 2;
const int DEV_UP = 3;
const int DEV_DOWN = 4;
const int AUTO_ON = 5;


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

