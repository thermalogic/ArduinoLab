/*
 Lab ToyCar motor

*/

#define forwardPWM 10
#define backPWM 9

#define turn_leftPWM 5
#define turn_rightPWM 6

int speed_level = 50;

void setup()
{
  pinMode(forwardPWM, OUTPUT);
  pinMode(backPWM, OUTPUT);
  digitalWrite(forwardPWM, LOW);
  digitalWrite(backPWM, LOW);
  delay(1000);
  analogWrite(forwardPWM, speed_level);
  analogWrite(backPWM, 0);
  delay(1000);
  analogWrite(forwardPWM, 0);
  analogWrite(backPWM, 100);
  delay(1000);
  // digitalWrite(forwardPWM, LOW);
  // digitalWrite(backPWM ,HIGH);
  // delay(1000);
  analogWrite(forwardPWM, 0);
  analogWrite(backPWM, 0);
  delay(1000);
  /*
  pinMode(turn_leftPWM, OUTPUT);
  pinMode(turn_rightPWM, OUTPUT);

  digitalWrite(turn_leftPWM, LOW);
  digitalWrite(turn_rightPWM ,LOW);
  analogWrite(turn_leftPWM, 100);
  analogWrite(turn_rightPWM, 0);
  delay(100);
  digitalWrite(turn_leftPWM, LOW);
  digitalWrite(turn_rightPWM ,LOW);
  delay(1000);
  analogWrite(turn_leftPWM, 0);
  analogWrite(turn_rightPWM, 100);
  delay(100);
  digitalWrite(turn_leftPWM, LOW);
  digitalWrite(turn_rightPWM ,LOW);
 */
}

void loop()
{
}
