/*
 Lab 2WD 1 -  two wheel with LS298N
 Motor Red  +  High ->  Forward
 Motor Black -  High -> Back
 
*/

#define LeftForward 3  // Motor Red +   LS298N IN4 -> Arduino Pin3
#define LeftBack 4     // Motor  black - LS298N IN3 -> Arduino Pin4
#define RightForward 8   // Motor balck -  LS298N IN1-> Arduino Pin8
#define RightBack 7      // Motor red +   LS298N IN2 -> Arduino Pin7

void setup() {
    pinMode(LeftForward,OUTPUT);
    pinMode(LeftBack,OUTPUT);
    pinMode(RightForward,OUTPUT);
    pinMode(RightBack,OUTPUT);
    initCar();
  
 }

void loop() {
    delay(1000);  
    go(); 
    delay(2000); 
    back();
    delay(2000);  
    turnLeft();
    delay(2000);      
    turnRight();
 
}

void initCar(){
	//默认全是低电平 停止状态
  digitalWrite(LeftForward,LOW); 
	digitalWrite(LeftBack,LOW);
	digitalWrite(RightForward,LOW); 
	digitalWrite(RightBack,LOW);
}

void go(){
  // 左轮前进
  digitalWrite(LeftForward,HIGH); 
	digitalWrite(LeftBack,LOW); 
  // 右轮前进
	digitalWrite(RightForward,HIGH); 
	digitalWrite(RightBack,LOW); 
}

void back(){
  //左轮后退
  digitalWrite(LeftForward,LOW); 
	digitalWrite(LeftBack,HIGH); 
  //右轮后退
	digitalWrite(RightForward,LOW); 
	digitalWrite(RightBack,HIGH); 
}

/* 左转 */
void turnLeft(){
  //左轮不动
  digitalWrite(LeftForward,LOW); 
	digitalWrite(LeftBack,LOW);
  // 右轮前进
	digitalWrite(RightForward,HIGH); 
	digitalWrite(RightBack,LOW); 
}

/* 右转 */
void turnRight(){
  // 左轮前进
  digitalWrite(LeftForward,HIGH); 
	digitalWrite(LeftBack,LOW); 
  // 右轮不动
  digitalWrite(RightForward,LOW); 
	digitalWrite(RightBack,LOW);
}

void stopCar(){
	initCar();
}