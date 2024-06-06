/* 
   Servo S90

    注意：使用GPIO 8，不使用 电机驱动等模块已经使用的GPIO,便于集成
         GPIO 12无效，绝对不能使用GPIO18,19会使的芯片的USB失效
*/
#ifndef SERVO_H
#define SERVO_H

#include <ESP32Servo.h>

// car action code
const int SERVO_CLOCKWISE = 1;
const int SERVO_ANTI_CLOCKWISE = 2;
int steps = 5;

// create servo object to control a servo
Servo ultrasonic_servo;
// 16 servo objects can be created on the ESP32

int cur_pos = 0;  // variable to store the servo position
// Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33
// Possible PWM GPIO pins on the ESP32-S2: 0(used by on-board button),1-17,18(used by on-board LED),19-21,26,33-42
// Possible PWM GPIO pins on the ESP32-S3: 0(used by on-board button),1-21,35-45,47,48(used by on-board LED)
// Possible PWM GPIO pins on the ESP32-C3: 0(used by on-board button),1-7,8(used by on-board LED),9-10,18-21

int ultrasonic_servo_pin = 2;

int pos=90;

void ultrasonic_servo_turning() {
  for (pos = 90; pos >= 0; pos -= 1) {  // goes from 180 degrees to 0 degrees
    ultrasonic_servo.write(pos);          // tell servo to go to position in variable 'pos'
    delay(15);                          // waits 15ms for the servo to reach the position
  }
  delay(1000);
  for (pos = 0; pos <= 180; pos += 1) {  // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    ultrasonic_servo.write(pos);  // tell servo to go to position in variable 'pos'
    delay(15);                  // waits 15ms for the servo to reach the position
  }
  delay(1000);
  for (pos = 180; pos >= 90; pos -= 1) {  // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    ultrasonic_servo.write(pos);  // tell servo to go to position in variable 'pos'
    delay(15);                  // waits 15ms for the servo to reach the position
  }
  delay(1000);
}

void ultrasonic_turning_clockwise() {
  for (int i = 0; i < steps; i++) {  // goes from 180 degrees to 0 degrees
    cur_pos -= 1;
//   Serial.println(cur_pos);
    if (cur_pos <= 0) { cur_pos = 0; }
    ultrasonic_servo.write(cur_pos);  // tell servo to go to position in variable 'pos'
    delay(15);                      // waits 15ms for the servo to reach the position
  }
}

void ultrasonic_turning_anti_clockwise() {
  for (int i = 0; i < steps; i++) {  // goes from 180 degrees to 0 degrees
    cur_pos += 1;
    Serial.println(cur_pos);
    if (cur_pos >= 180) { cur_pos = 180; }
    ultrasonic_servo.write(cur_pos);  // tell servo to go to position in variable 'pos'
    delay(15);                      // waits 15ms for the servo to reach the position
  }
}

void ultrasonic_servo_action(int servo_cmd) {
  switch (servo_cmd) {
    case SERVO_CLOCKWISE:
      Serial.println("SERVO_CLOCKWISE");
      ultrasonic_turning_clockwise();
      break;
    case SERVO_ANTI_CLOCKWISE:
      Serial.println("SERVO_ANTI_CLOCKWISE");
      ultrasonic_turning_anti_clockwise();
      break;
    default:
      break;
  }  // switch
};

void setup_servo() {
  //Allow allocation of all timers
  ultrasonic_servo.attach(ultrasonic_servo_pin, 500, 2500); 
  
  int init_angle = ultrasonic_servo.read();     
  if (init_angle != pos)
  {
    ultrasonic_servo.write(pos);
  };
  cur_pos = pos;
}

void loop_servo() {
   
}
#endif /* SERVO_H */