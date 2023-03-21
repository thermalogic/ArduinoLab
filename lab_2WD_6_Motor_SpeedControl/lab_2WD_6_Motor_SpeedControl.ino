/*
 Lab 2WD 1 -  two wheel with LS298N
 Motor Red  +  High ->  Forward
 Motor Black -  High -> Back
 
*/
//正反转控制
#define LeftForward 8   // Motor balck -  LS298N IN1-> Arduino Pin8
#define LeftBack 7      // Motor red +   LS298N IN2 -> Arduino Pin7
#define RightForward 3  // Motor Red +   LS298N IN4 -> Arduino Pin3
#define RightBack 4     // Motor  black - LS298N IN3 -> Arduino Pin4
// 速度控制
#define leftPWM 6
#define rightPWM 5
#define SPEED_LEVEL_0 0  //stop
#define SPEED_LEVEL_1 1
#define SPEED_LEVEL_2 2  //max
int speed_level1= 125; // 太低驱动不了
int speed_level2 = 250;
int speed_level;

void initCar() {
  //默认全是低电平 停止状态
  digitalWrite(LeftForward, LOW);
  digitalWrite(LeftBack, LOW);
  digitalWrite(RightForward, LOW);
  digitalWrite(RightBack, LOW);
}

void go() {
  // 左轮前进
  digitalWrite(LeftForward, HIGH);
  digitalWrite(LeftBack, LOW);
  // 右轮前进
  digitalWrite(RightForward, HIGH);
  digitalWrite(RightBack, LOW);
}

void back() {
  //左轮后退
  digitalWrite(LeftForward, LOW);
  digitalWrite(LeftBack, HIGH);
  //右轮后退
  digitalWrite(RightForward, LOW);
  digitalWrite(RightBack, HIGH);
}

/* 左转 */
void turnLeft() {
  //左轮不动
  digitalWrite(LeftForward, LOW);
  digitalWrite(LeftBack, LOW);
  // 右轮前进
  digitalWrite(RightForward, HIGH);
  digitalWrite(RightBack, LOW);
}

/* 右转 */
void turnRight() {
  // 左轮前进
  digitalWrite(LeftForward, HIGH);
  digitalWrite(LeftBack, LOW);
  // 右轮不动
  digitalWrite(RightForward, LOW);
  digitalWrite(RightBack, LOW);
}

void stopCar() {
  initCar();
}

void setup() {
  pinMode(LeftForward, OUTPUT);
  pinMode(LeftBack, OUTPUT);
  pinMode(RightForward, OUTPUT);
  pinMode(RightBack, OUTPUT);
  initCar();

  // speedcontrol
  pinMode(leftPWM, OUTPUT);
  pinMode(rightPWM, OUTPUT);
  analogWrite(leftPWM, 0);
  analogWrite(rightPWM, 0);
 
  delay(2000);
  analogWrite(leftPWM, speed_level1);
  analogWrite(rightPWM, speed_level1);
  go();
  delay(2000);
  analogWrite(leftPWM, speed_level2);
  analogWrite(rightPWM, speed_level2);
  go();
  delay(4000);
  analogWrite(leftPWM, speed_level1);
  analogWrite(rightPWM, speed_level2);
  go();
  delay(4000);
  analogWrite(leftPWM, speed_level2);
  analogWrite(rightPWM, speed_level1);
  go();
  delay(4000);
  analogWrite(leftPWM, 0);
  analogWrite(rightPWM, speed_level2);
  go();
  delay(4000);
  analogWrite(leftPWM,speed_level2);
  analogWrite(rightPWM, 0);
  go();
  delay(4000);
  stopCar() ;
}

void loop() {
 
}
