/*
 Motor Black -  High -> Forward
 Motor Red +  High -> Back 

*/
#define LeftForward 4 // Motor Black -     LS298N IN1 -> Arduino Pin4 
#define LeftBack 5  // Motor Red     +     LS298N IN2 -> Arduino Pin5 

void setup() {
    pinMode(LeftForward,OUTPUT);
    pinMode(LeftBack,OUTPUT);
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
	digitalWrite(LeftForward,LOW); 
	digitalWrite(LeftBack,LOW);
}

void go(){
	digitalWrite(LeftForward,HIGH); 
	digitalWrite(LeftBack,LOW); //左轮前进
}

void back(){
	digitalWrite(LeftForward,LOW); 
	digitalWrite(LeftBack,HIGH); //左轮后退
}

void stopCar(){
	initCar();
}