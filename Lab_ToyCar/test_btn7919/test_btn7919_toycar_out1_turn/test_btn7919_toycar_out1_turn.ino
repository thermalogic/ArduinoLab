/*
 out1,舵机
*/

#define forward 9
#define back 10

#define turn 11

int speed_level = 250;

void setup()
{
  pinMode(forward, OUTPUT);
  pinMode(back, OUTPUT);
  analogWrite(forward, 0);
  analogWrite(back,  0);
  analogWrite(forward, speed_level );
  analogWrite(back,  0);
  
  pinMode(turn, OUTPUT);
  analogWrite(turn,0);
  delay(5000);
}

void loop()
{
  analogWrite(forward, speed_level );
  analogWrite(back,  0);
  analogWrite(turn, 0);
  delay(1000);
  analogWrite(forward,  0);
  analogWrite(back,  speed_level);
  analogWrite(turn,speed_level);
  delay(1000);  
}
