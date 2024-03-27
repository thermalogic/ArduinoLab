#include <Servo.h>

Servo vertical_servo;
Servo horizontal_servo;

void setup() {
  vertical_servo.attach(3);
  horizontal_servo.attach(6);
  delay(1000);
}

void demo_servo(Servo cur_servo) {
  // rotate counter-clockwise full-speed
  cur_servo.writeMicroseconds(1000);
  delay(2000);

  // rotation stopped
  cur_servo.writeMicroseconds(1500);
  delay(1000);

  // rotate clockwise full-speed
  cur_servo.writeMicroseconds(2000);
  delay(2000);

  // rotation stopped
  cur_servo.writeMicroseconds(1500);
  delay(2000);
}

void loop() {
  demo_servo(vertical_servo);
  demo_servo(horizontal_servo);
}
