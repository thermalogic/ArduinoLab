#include <Servo.h>

Servo vertical_servo;

int i=0;

void setup() {
  vertical_servo.attach(3);
  i=0;
  delay(1000);
}

void demo_servo(Servo cur_servo) {
  // rotate counter-clockwise full-speed 0度
  cur_servo.writeMicroseconds(544);
  delay(2000);

  // rotation stopped 90
  cur_servo.writeMicroseconds(1500);
  delay(1000);
 // 0度
  cur_servo.writeMicroseconds(544);
  delay(2000);

// rotate clockwise full-speed 180度
 cur_servo.writeMicroseconds(2544);
  delay(2000);

  // rotation stopped 度
 cur_servo.writeMicroseconds(1500);
 delay(2000);
}

void loop() {
  while (i<2)
   {
     demo_servo(vertical_servo);
     i++;
   }
} 
