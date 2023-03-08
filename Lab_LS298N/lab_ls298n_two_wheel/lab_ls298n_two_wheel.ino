/*
 Motor Black -  High -> Forward
 Motor Red +  High -> Back 

*/

#define LeftForward 4   // Motor Black -     LS298N IN1 -> Arduino Pin4 
#define LeftBack 5      // Motor Red     +     LS298N IN2 -> Arduino Pin5 
#define RightForward 6  // Motor Black -     LS298N IN3 -> Arduino Pin6 
#define RightBack 7    // Motor Red     +     LS298N IN4 -> Arduino Pin7 

void setup() {
    pinMode(LeftForward,OUTPUT);
    pinMode(LeftBack,OUTPUT);
    pinMode(RightForward,OUTPUT);
    pinMode(RightBack,OUTPUT);
    initCar();
    delay(1000);  
    go(); 
    delay(1000); 
    stopCar();
    delay(1000);     
    back();
    delay(1000);  
    turnLeft();
    delay(1000);      
    turnRight();
    delay(1000); 
    stopCar();
 }

void loop() {
 
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