/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald

 modified for the ESP32 on March 2017
 by John Bennett

 see http://www.arduino.cc/en/Tutorial/Sweep for a description of the original code

 * Different servos require different pulse widths to vary servo angle, but the range is 
 * an approximately 500-2500 microsecond pulse every 20ms (50Hz). In general, hobbyist servos
 * sweep 180 degrees, so the lowest number in the published range for a particular servo
 * represents an angle of 0 degrees, the middle of the range represents 90 degrees, and the top
 * of the range represents 180 degrees. So for example, if the range is 1000us to 2000us,
 * 1000us would equal an angle of 0, 1500us would equal 90 degrees, and 2000us would equal 1800
 * degrees.
 * 
 * Circuit: (using an ESP32 Thing from Sparkfun)
 * Servo motors have three wires: power, ground, and signal. The power wire is typically red,
 * the ground wire is typically black or brown, and the signal wire is typically yellow,
 * orange or white. Since the ESP32 can supply limited current at only 3.3V, and servos draw
 * considerable power, we will connect servo power to the VBat pin of the ESP32 (located
 * near the USB connector). THIS IS ONLY APPROPRIATE FOR SMALL SERVOS. 
 * 
 * We could also connect servo power to a separate external
 * power source (as long as we connect all of the grounds (ESP32, servo, and external power).
 * In this example, we just connect ESP32 ground to servo ground. The servo signal pins
 * connect to any available GPIO pins on the ESP32 (in this example, we use pin 18.
 * 
 * In this example, we assume a Tower Pro MG995 large servo connected to an external power source.
 * The published min and max for this servo is 1000 and 2000, respectively, so the defaults are fine.
 * These values actually drive the servos a little past 0 and 180, so
 * if you are particular, adjust the min and max values to match your needs.
 
 The default pulse width range for servo.write() is 544us to 2400us, 

 G996R
 #define MIN_PULSE_WIDTH 600
#define MAX_PULSE_WIDTH 2600
#define FREQUENCY 50
   771 to 2740

产品数据是500-2500
测试结果
#define MIN_PULSE_WIDTH 544
#define MAX_PULSE_WIDTH 2544 
刚好180度

正向舵机：逆时针转，角度是逆时针0-180

180度舵机有反馈，360度没有

金属舵轮安装角度只能是0.90,180,不能是其他？ 

这样
* 水平转动没有问题，初始90度，左右个各90度
* 上下转动可能不合适，如向下转多， 向上少

要向下转更多，用塑料舵盘，

360度的舵机无法控制角度，只能控制其转动方向和速度，而且速度是固定的数值，


 */

#include <ESP32Servo.h>

#define FREQUENCY 50
#define MIN_PULSE_WIDTH 544
#define MAX_PULSE_WIDTH 2544

// create servo object to control a servo
Servo vertical_servo;
Servo horizontal_servo;
// 16 servo objects can be created on the ESP32

int pos = 0;  // variable to store the servo position
// Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33
// Possible PWM GPIO pins on the ESP32-S2: 0(used by on-board button),1-17,18(used by on-board LED),19-21,26,33-42
// Possible PWM GPIO pins on the ESP32-S3: 0(used by on-board button),1-21,35-45,47,48(used by on-board LED)
// Possible PWM GPIO pins on the ESP32-C3: 0(used by on-board button),1-7,8(used by on-board LED),9-10,18-21
#if defined(CONFIG_IDF_TARGET_ESP32S2) || defined(CONFIG_IDF_TARGET_ESP32S3)
int vertical_servo_pin = 2;
int horizontal_servo_pin = 15;
#elif defined(CONFIG_IDF_TARGET_ESP32C3)
int vertical_servo_pin = 7;
int horizontal_servo_pin =2;
#else
int vertical_servo_pin = 2;
int horizontal_servo_pin = 15;
#endif

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

void horizontal_servo_turning(){

  for (pos = 45; pos >= 25; pos -= 1) {  // goes from 180 degrees to 0 degrees
  horizontal_servo.write(pos);           // tell servo to go to position in variable 'pos'
  delay(15);                             // waits 15ms for the servo to reach the position
}
delay(1000);
for (pos = 25; pos <= 170; pos += 1) {  // goes from 0 degrees to 180 degrees
  // in steps of 1 degree
  horizontal_servo.write(pos);  // tell servo to go to position in variable 'pos'
  delay(15);                    // waits 15ms for the servo to reach the position
}
delay(1000);

for (pos = 170; pos >= 90; pos -= 1) {  // goes from 0 degrees to 180 degrees
  // in steps of 1 degree
  horizontal_servo.write(pos);  // tell servo to go to position in variable 'pos'
  delay(15);                    // waits 15ms for the servo to reach the position
}
}

void setup() {
  //Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  vertical_servo.setPeriodHertz(FREQUENCY);                                     // standard 50 hz servo
  vertical_servo.attach(vertical_servo_pin, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);  // attaches the servo on pin 18 to the servo object
  vertical_servo.write(90);                                                     // tell servo to go to position in variable 'pos'

  horizontal_servo.setPeriodHertz(FREQUENCY);                                       // standard 50 hz servo
  horizontal_servo.attach(horizontal_servo_pin, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);  // attaches the servo on pin 18 to the servo object
  horizontal_servo.write(90);                                                       // tell servo to go to position in variable 'pos'

  // using default min/max of 1000us and 2000us
  // different servos may require different min/max settings
  // for an accurate 0 to 180 sweep
  delay(2000);
 vertical_servo_turning();
  horizontal_servo_turning();
}

void loop() {
}
