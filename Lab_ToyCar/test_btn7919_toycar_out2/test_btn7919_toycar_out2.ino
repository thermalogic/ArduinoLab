/*
 out2
*/

#define forward 10
#define back 9

int speed_level = 250;

void setup()
{
  pinMode(forward, OUTPUT);
  pinMode(back, OUTPUT);
  analogWrite(forward, 0);
  analogWrite(back,  0);
  analogWrite(forward, 0);
  analogWrite(back, speed_level);
  delay(5000);
}

void loop()
{
  analogWrite(forward, 0);
  analogWrite(back, speed_level);
  delay(2000);
  analogWrite(forward, speed_level );
  analogWrite(back,  0);
  delay(2000);
  
}
