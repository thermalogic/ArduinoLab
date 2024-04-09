
/* MiniCar with ESP32-C3
      Motor
*/
#ifndef DEVICE_H
#define DEVICE_H

#define LEFT_FORWARD 10 // AIN1
#define LEFT_BACK 6     // AIN2 6
#define RIGHT_FORWARD 7 //  BIN1
#define RIGHT_BACK 11   // BIN2

// motor action code
const int DEV_GO = 1;
const int DEV_BACK = 2;
const int DEV_LEFT = 4;
const int DEV_RIGHT = 5;
const int DEV_STOP = 3;

int cur_cmd = DEV_STOP;

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

void do_action()
{
  switch (cur_cmd)
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

  cur_cmd = DEV_STOP;

  pinMode(LEFT_FORWARD, OUTPUT);
  pinMode(LEFT_BACK, OUTPUT);
  pinMode(RIGHT_FORWARD, OUTPUT);
  pinMode(RIGHT_BACK, OUTPUT); 
 
}

void loop_motor()
{
   do_action();
   delay(2000);
  
}

#endif /* MOTOR_H */