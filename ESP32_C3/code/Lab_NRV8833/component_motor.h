
/* MiniCar with ESP32-C3
      Motor
*/
#ifndef MOTOR_H
#define MOTOR_H

#define LEFT_FORWARD 2 // AIN1 绿色
#define LEFT_BACK 3     // AIN2 黄色

#define RIGHT_FORWARD 6 //  BIN1
#define RIGHT_BACK 10   // BIN2

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
  digitalWrite(LEFT_FORWARD, HIGH);
  digitalWrite(LEFT_BACK, LOW);
  digitalWrite(RIGHT_FORWARD, HIGH);
  digitalWrite(RIGHT_BACK, LOW);
}

void motor_back()
{
  digitalWrite(LEFT_FORWARD, LOW);
  digitalWrite(LEFT_BACK, HIGH);
  digitalWrite(RIGHT_FORWARD, LOW);
  digitalWrite(RIGHT_BACK, HIGH);
}

void motor_stop()
{
  digitalWrite(LEFT_FORWARD, LOW);
  digitalWrite(LEFT_BACK, LOW);
  digitalWrite(RIGHT_FORWARD, LOW);
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

  
 digitalWrite(LEFT_FORWARD,LOW);
 digitalWrite(LEFT_BACK, LOW);
 
}

void loop_motor()
{
  
}

#endif /* MOTOR_H */