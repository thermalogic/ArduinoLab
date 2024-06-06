#ifndef BTN7919_H
#define BTN7919_H

/*
 右电机 红线 -> 电机1 out1 线圈侧 -> BTN7919 PMW2 -> GPIO 33 黄色
 右电机 黑线 -> 电机1 out1 开关侧 -> BTN7919 PMW1 -> GPIO 32 绿色

 左电机 红线 -> 电机2 out2 开关侧 -> BTN7919 PMW4 -> GPIO 12 黄色
 左电机 黑线 -> 电机2 out2 线圈侧 -> BTN7919 PMW3 -> GPIO 14 绿色 
*/

// Motor right
int motor_right_Pin_Red = 33;   // PMW2 黄色
int motor_right_Pin_Black = 32;  // PMW1 绿色

// Motor left 
int motor_left_Pin_Red = 12;   //  PMW4 黄色
int motor_left_Pin_Black = 14; //  PMW3  绿色

const int resolution = 8;

// car action code
const int DEV_GO = 1;
const int DEV_BACK = 2;
const int DEV_LEFT = 3;
const int DEV_RIGHT = 4;
const int DEV_STOP = 5;
//
const int DEV_SPEED_UP = 6;
const int DEV_SPEED_DOWN = 7;
// car running state
int car_state = DEV_STOP;

// PWM - speed
int left_speed = 200;
int right_speed = 200;
const int turn_speed_diff = 120;
const int speed_step = 10;

void car_forward() {
  // Moving Forward
  digitalWrite(motor_right_Pin_Red, HIGH);
  digitalWrite(motor_right_Pin_Black, LOW);
  //ledcWrite(pwmChannel_motor_right_forward, right_speed);

  digitalWrite(motor_left_Pin_Red, HIGH);
  digitalWrite(motor_left_Pin_Black, LOW);
  //ledcWrite(pwmChannel_motor_left_forward, left_speed);
}

void car_back() {
  // Move DC motor backwards at maximum speed
  digitalWrite(motor_right_Pin_Red, LOW);
  digitalWrite(motor_right_Pin_Black, HIGH);
  //ledcWrite(pwmChannel_motor_right_backward, right_speed);

  digitalWrite(motor_left_Pin_Red, LOW);
  digitalWrite(motor_left_Pin_Black, HIGH);
  //ledcWrite(pwmChannel_motor_left_backward, left_speed);
}

void car_stop() {
  // Stop the DC motor
  digitalWrite(motor_right_Pin_Red, LOW);
  digitalWrite(motor_right_Pin_Black, LOW);
  //ledcWrite(pwmChannel_motor_right_forward, 0);
  //ledcWrite(pwmChannel_motor_right_backward, 0);

  digitalWrite(motor_left_Pin_Red, LOW);
  digitalWrite(motor_left_Pin_Black, LOW);
  //ledcWrite(pwmChannel_motor_left_forward, 0);
  //ledcWrite(pwmChannel_motor_left_backward, 0);
}

void car_turn_left() {
  // turn_left
  digitalWrite(motor_right_Pin_Red, HIGH);
  digitalWrite(motor_right_Pin_Black, LOW);
  //ledcWrite(pwmChannel_motor_right_forward, right_speed);

  digitalWrite(motor_left_Pin_Red, LOW);
  digitalWrite(motor_left_Pin_Black, LOW);
  int left_turn_speed = right_speed - turn_speed_diff;
  if (left_turn_speed < 0) {
    left_turn_speed = 0;
  }
  //ledcWrite(pwmChannel_motor_left_forward, left_turn_speed);
}

void car_turn_right() {
  // turn right
  digitalWrite(motor_right_Pin_Red, LOW);
  digitalWrite(motor_right_Pin_Black, LOW);
   left_speed = 200;
  //ledcWrite(pwmChannel_motor_left_forward, left_speed);

  digitalWrite(motor_left_Pin_Red, HIGH);
  digitalWrite(motor_left_Pin_Black, LOW);
 
  int right_turn_speed = left_speed - turn_speed_diff;
  if (right_turn_speed < 0) {
    right_turn_speed = 0;
  }
  //ledcWrite(pwmChannel_motor_right_forward, right_turn_speed);
}

void running_with_new_speed() {
  switch (car_state) {
    case DEV_GO:
      car_forward();
      break;
    case DEV_BACK:
      car_back();
      break;
    case DEV_LEFT:
      car_turn_left();
      break;
    case DEV_RIGHT:
      car_turn_right();
      break;
    default:
      break;
  }
}

void car_speed_up() {
  right_speed += speed_step;
  if (right_speed > 255) {
    right_speed = 255;
  }

  left_speed += speed_step;
  if (left_speed > 255) {
    left_speed = 255;
  }
  running_with_new_speed();
}

void car_speed_down() {
  right_speed -= speed_step;
  if (right_speed < 0) {
    right_speed = 0;
  }

  left_speed -= speed_step;
  if (left_speed < 0) {
    left_speed = 0;
  }
  running_with_new_speed();
}

void car_action(int car_cmd) {
  switch (car_cmd) {
    case DEV_GO:
      car_forward();
      car_state = DEV_GO;
      break;
    case DEV_LEFT:
      car_turn_left();
      car_state = DEV_LEFT;
      delay(100);
      car_stop();
      car_state = DEV_STOP;
      break;
    case DEV_RIGHT:
      car_turn_right();
      car_state = DEV_RIGHT;
      delay(100);
      car_stop();
      car_state = DEV_STOP;
      break;
    case DEV_BACK:
      car_back();
      car_state = DEV_BACK;
      break;
    case DEV_STOP:
      car_stop();
      car_state = DEV_STOP;
      break;
    case DEV_SPEED_UP:
      car_speed_up();
      break;
    case DEV_SPEED_DOWN:
      car_speed_down();
      break;
    default:
      break;
  }  // switch
};

void setup_btn7919() {
  // sets the pins as outputs:
  pinMode(motor_right_Pin_Red, OUTPUT);
  pinMode(motor_right_Pin_Black, OUTPUT);

  pinMode(motor_left_Pin_Red, OUTPUT);
  pinMode(motor_left_Pin_Black, OUTPUT);

  // configure LED PWM functionalitites
  //ledcSetup(pwmChannel_motor_right_forward, freq, resolution);
  //ledcAttachPin(motor_right_Pin1, pwmChannel_motor_right_forward);

  //ledcSetup(pwmChannel_motor_left_forward, freq, resolution);
  //ledcAttachPin(motor_left_Pin1, pwmChannel_motor_left_forward);

  //ledcSetup(pwmChannel_motor_right_backward, freq, resolution);
  //ledcAttachPin(motor_right_Pin2, pwmChannel_motor_right_backward);
  //ledcSetup(pwmChannel_motor_left_backward, freq, resolution);
  //ledcAttachPin(motor_left_Pin2, pwmChannel_motor_left_backward);
}
 

void loop_btn7919() {
}

#endif /* BTN7919_H */