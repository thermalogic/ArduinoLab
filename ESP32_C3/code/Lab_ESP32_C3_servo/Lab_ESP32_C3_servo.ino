/* 
   Servo S90

    注意：使用GPIO 8，不使用                                                                                   电机驱动等模块已经使用的GPIO,便于集成
    使用GPIO 12无效，绝对不能使用GPIO18,19会使的芯片的USB失效
*/

#include <ESP32Servo.h>

#define FREQUENCY 50
#define MIN_PULSE_WIDTH 544
#define MAX_PULSE_WIDTH 2544

// create servo object to control a servo
Servo vertical_servo;
// 16 servo objects can be created on the ESP32

int pos = 0;  // variable to store the servo position
// Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33
// Possible PWM GPIO pins on the ESP32-S2: 0(used by on-board button),1-17,18(used by on-board LED),19-21,26,33-42
// Possible PWM GPIO pins on the ESP32-S3: 0(used by on-board button),1-21,35-45,47,48(used by on-board LED)
// Possible PWM GPIO pins on the ESP32-C3: 0(used by on-board button),1-7,8(used by on-board LED),9-10,18-21

int vertical_servo_pin =6;

void vertical_servo_turning() {
  for (pos = 90; pos >= 0; pos -= 1) {  // goes from 180 degrees to 0 degrees
    vertical_servo.write(pos);          // tell servo to go to position in variable 'pos'
    delay(15);                          // waits 15ms for the servo to reach the position
  }
  delay(1000);
  for (pos = 0; pos <= 180; pos += 1) {  // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    vertical_servo.write(pos);  // tell servo to go to position in variable 'pos'
    delay(15);                  // waits 15ms for the servo to reach the position
  }
  delay(1000);
  for (pos = 180; pos >= 90; pos -= 1) {  // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    vertical_servo.write(pos);  // tell servo to go to position in variable 'pos'
    delay(15);                  // waits 15ms for the servo to reach the position
  }
  delay(1000);
}


void setup() {
  //Allow allocation of all timers
 
  vertical_servo.setPeriodHertz(FREQUENCY);                                     // standard 50 hz servo
  vertical_servo.attach(vertical_servo_pin, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);  // attaches the servo on pin 18 to the servo object
  vertical_servo.write(90);                                                     // tell servo to go to position in variable 'pos'

  // using default min/max of 1000us and 2000us
  // different servos may require different min/max settings
  // for an accurate 0 to 180 sweep
  delay(2000);
  vertical_servo_turning();
}

void loop() {
}
