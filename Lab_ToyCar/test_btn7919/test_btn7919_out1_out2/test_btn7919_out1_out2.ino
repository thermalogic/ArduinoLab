/*
 two motors
*/


#define left_forward 9
#define left_back 10

#define right_forward 5
#define right_back 6

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
  //analogWrite(right_forward, 0);
  //analogWrite(right_back,speed_level);
  delay(2000);
  
}
