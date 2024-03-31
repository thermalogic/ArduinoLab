/*
 two motors -esp32测试结果： 板子坏了
*/


#define left_forward 15 //p4
#define left_back 2     //p3

#define right_forward 21//p2
#define right_back 3//p1

int speed_level = 250;

void setup()
{
  pinMode(left_forward, OUTPUT);
  pinMode(left_back, OUTPUT);

  pinMode(right_forward, OUTPUT);
  pinMode(right_back, OUTPUT);
}

void loop()
{
  analogWrite(left_forward, speed_level );
  analogWrite(left_back,  0);
  
 analogWrite(right_forward, speed_level);
  analogWrite(right_back,0);
  
  delay(2000);
  analogWrite(left_forward,  0);
  analogWrite(left_back,  speed_level);
  
  analogWrite(right_forward, 0);
  analogWrite(right_back,speed_level);
  
  delay(2000);
  
}
