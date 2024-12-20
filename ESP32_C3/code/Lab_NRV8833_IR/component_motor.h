
/* MiniCar with ESP32-C3
      Motor
*/
#ifndef MOTOR_H
#define MOTOR_H

#define LEFT_FORWARD 01 // AIN1 绿色
#define LEFT_BACK 12     // AIN2 黄色

#define RIGHT_FORWARD 10//  BIN1 绿色
#define RIGHT_BACK 3   // BIN2 黄色

// motor action code
const int DEV_GO = 1;
const int DEV_BACK = 2;
const int DEV_LEFT = 3;
const int DEV_RIGHT = 4;
const int DEV_STOP = 5;

// PWM - speed
const int left_speed = 180;
const int right_speed = 180;
const int turn_speed_diff = 100;

void motor_forward()
{
  analogWrite(LEFT_FORWARD, left_speed);
  digitalWrite(LEFT_BACK, LOW);
  analogWrite(RIGHT_FORWARD, right_speed);
  digitalWrite(RIGHT_BACK, LOW);
}

void motor_back()
{
  analogWrite(LEFT_FORWARD,0);
  digitalWrite(LEFT_BACK, HIGH);
  analogWrite(RIGHT_FORWARD,0);
  digitalWrite(RIGHT_BACK, HIGH);
}

void motor_stop()
{
  analogWrite(LEFT_FORWARD, 0);
  digitalWrite(LEFT_BACK, LOW);
  analogWrite(RIGHT_FORWARD, 0);
  digitalWrite(RIGHT_BACK, LOW);
  
}

void motor_turn_left()
{
  analogWrite(LEFT_FORWARD, left_speed);
  digitalWrite(LEFT_BACK, LOW);
  analogWrite(RIGHT_FORWARD, left_speed - turn_speed_diff);
  digitalWrite(RIGHT_BACK, LOW);
}

void motor_turn_right()
{
  analogWrite(LEFT_FORWARD, left_speed - turn_speed_diff);
  digitalWrite(LEFT_BACK, LOW);
  analogWrite(RIGHT_FORWARD, left_speed);
  digitalWrite(RIGHT_BACK, LOW);
}

void motor_action(int motor_cmd)
{
  switch (motor_cmd)
  {
  case DEV_GO:
    motor_forward();
    break;
  case DEV_LEFT:
    motor_turn_left();
    break;
  case DEV_RIGHT:
    motor_turn_right();
    break;
  case DEV_BACK:
    motor_back();
    break;
  case DEV_STOP:
    motor_stop();
    break;
  default:
    break;
  } // switch
};

void setup_motor()
{
  pinMode(LEFT_FORWARD, OUTPUT);
  pinMode(LEFT_BACK, OUTPUT);
  pinMode(RIGHT_FORWARD, OUTPUT);
  pinMode(RIGHT_BACK, OUTPUT); 
 
}

void loop_motor()
{
  
}

#endif /* MOTOR_H */