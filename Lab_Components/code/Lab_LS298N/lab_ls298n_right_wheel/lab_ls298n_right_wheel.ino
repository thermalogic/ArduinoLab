/*
 Motor Black -  High -> Forward
 Motor Red +  High -> Back 

*/
#define RightForward 6 // Motor Black -     LS298N IN3 -> Arduino Pin6 
#define RightBack 7  // Motor Red     +     LS298N IN4 -> Arduino Pin7 

void setup() {
    pinMode(RightForward,OUTPUT);
    pinMode(RightBack,OUTPUT);
    initCar();
    delay(1000);  
    go(); 
    delay(2000); 
    stopCar();
    delay(1000);     
    back();
    delay(1000);  
    stopCar();
 }

void loop() {
 
}

void initCar(){
	//默认全是低电平 停止状态
	digitalWrite(RightForward,LOW); 
	digitalWrite(RightBack,LOW);
}

void go(){
	digitalWrite(RightForward,HIGH); 
	digitalWrite(RightBack,LOW); // 右轮前进
}

void back(){
	digitalWrite(RightForward,LOW); 
	digitalWrite(RightBack,HIGH); //右轮后退
}

void stopCar(){
	initCar();
}