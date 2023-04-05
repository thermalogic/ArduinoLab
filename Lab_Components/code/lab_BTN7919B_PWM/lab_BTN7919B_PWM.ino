/*
 Lab 2WD 1 -  two wheel with LS298N
 Motor Red  +  High ->  Forward
 Motor Black -  High -> Back
 
*/
// 速度控制
#define leftPWM 9
#define rightPWM 10

#define SPEED_LEVEL_0 0  //stop
#define SPEED_LEVEL_1 1
#define SPEED_LEVEL_2 2  //max
int speed_level1= 125; // 太低驱动不了
int speed_level2 = 250;
int speed_level;


void setup() {
  // speedcontrol
  pinMode(leftPWM, OUTPUT);
  pinMode(rightPWM, OUTPUT);
  analogWrite(leftPWM, 0);
  analogWrite(rightPWM, 0);
 
  delay(2000);
  analogWrite(leftPWM, speed_level1);
  analogWrite(rightPWM, speed_level1);
  delay(0000);
  analogWrite(leftPWM, speed_level2);
  analogWrite(rightPWM, speed_level2);
  delay(2000);
  analogWrite(leftPWM,0);
  analogWrite(rightPWM, 0);
   analogWrite(leftPWM, speed_level2);
  analogWrite(rightPWM, speed_level2);
  
}

void loop() {
 
}
