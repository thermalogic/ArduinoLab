/*
TCRT5000红外反射光电开关寻迹传感器模块
程序二，接到A0模拟口，串口波形，可以测量距离
*/

int tcrt;

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  tcrt = analogRead(A0);
  analogWrite(13, tcrt / 4);
  Serial.println(tcrt);
  delay(500);
}
