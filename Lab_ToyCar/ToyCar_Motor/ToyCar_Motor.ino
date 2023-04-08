/*
 Lab ToyCar motor
 Main Motor - green ->D1 ->p1-> Arduino D9  
 Main Motor - black ->D2 ->p2-> Arduino D10 
 
 Turn Motor - green ->D1 ->p1-> Arduino D9 

*/

#define forwardPWM 9
#define backPWM 10

#define turn_leftPWM 5
#define turn_rightPWM 6

int speed_level = 250;

void setup()
{
  pinMode(forwardPWM, OUTPUT);
  pinMode(backPWM, OUTPUT);
  /*igitalWrite(forwardPWM, LOW);
  digitalWrite(backPWM, LOW);
  delay(1000);
  analogWrite(forwardPWM, speed_level);
  analogWrite(backPWM, 0);
  delay(2000);
  analogWrite(forwardPWM, 0);
  analogWrite(backPWM, speed_level);
  delay(2000);
  // digitalWrite(forwardPWM, LOW);
  // digitalWrite(backPWM ,HIGH);
  // delay(1000);
  analogWrite(forwardPWM, 0);
  analogWrite(backPWM, 0);
  delay(2000);
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
  analogWrite(forwardPWM, 0);
  analogWrite(backPWM, speed_level);
  delay(2000);
  analogWrite(forwardPWM,speed_level);
  analogWrite(backPWM, 0);
  delay(2000);
  
}
