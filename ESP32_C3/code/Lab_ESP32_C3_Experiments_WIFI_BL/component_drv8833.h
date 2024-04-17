#ifndef DRV8833_H
#define DRV8833_H

// Motor A Right OK!
int motor_right_Pin1 = 1;  // AIN1绿色
int motor_right_Pin2 = 0;  // AIN2黄色

// Motor B left
int motor_left_Pin1 = 3;   //  BIN1 绿色
int motor_left_Pin2 = 10;  // BIN2 黄色

// Setting PWM properties
const int freq = 30000;
const int pwmChannel_motor_right_forward = 0;
const int pwmChannel_motor_left_forward = 1;
const int pwmChannel_motor_right_backward = 2;
const int pwmChannel_motor_left_backward = 3;

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
  digitalWrite(motor_right_Pin1, HIGH);
  digitalWrite(motor_right_Pin2, LOW);
  ledcWrite(pwmChannel_motor_right_forward, right_speed);

  digitalWrite(motor_left_Pin1, HIGH);
  digitalWrite(motor_left_Pin2, LOW);
  ledcWrite(pwmChannel_motor_left_forward, left_speed);
}

void car_back() {
  // Move DC motor backwards at maximum speed
  digitalWrite(motor_right_Pin1, LOW);
  digitalWrite(motor_right_Pin2, HIGH);
  ledcWrite(pwmChannel_motor_right_backward, right_speed);

  digitalWrite(motor_left_Pin1, LOW);
  digitalWrite(motor_left_Pin2, HIGH);
  ledcWrite(pwmChannel_motor_left_backward, left_speed);
}

void car_stop() {
  // Stop the DC motor
  digitalWrite(motor_right_Pin1, LOW);
  digitalWrite(motor_right_Pin2, LOW);
  ledcWrite(pwmChannel_motor_right_forward, 0);
  ledcWrite(pwmChannel_motor_right_backward, 0);

  digitalWrite(motor_left_Pin1, LOW);
  digitalWrite(motor_left_Pin2, LOW);
  ledcWrite(pwmChannel_motor_left_forward, 0);
  ledcWrite(pwmChannel_motor_left_backward, 0);
}

void car_turn_left() {
  // turn_left
  digitalWrite(motor_right_Pin1, HIGH);
  digitalWrite(motor_right_Pin2, LOW);
  ledcWrite(pwmChannel_motor_right_forward, right_speed);

  digitalWrite(motor_left_Pin1, HIGH);
  digitalWrite(motor_left_Pin2, LOW);
  int left_turn_speed = right_speed - turn_speed_diff;
  if (left_turn_speed < 0) {
    left_turn_speed = 0;
  }
  ledcWrite(pwmChannel_motor_left_forward, left_turn_speed);
}

void car_turn_right() {
  // turn right
  digitalWrite(motor_left_Pin1, HIGH);
  digitalWrite(motor_left_Pin2, LOW);
  left_speed = 200;
  ledcWrite(pwmChannel_motor_left_forward, left_speed);

  digitalWrite(motor_right_Pin1, HIGH);
  digitalWrite(motor_right_Pin2, LOW);
  int right_turn_speed = left_speed - turn_speed_diff;
  if (right_turn_speed < 0) {
    right_turn_speed = 0;
  }
  ledcWrite(pwmChannel_motor_right_forward, right_turn_speed);
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
      break;
    case DEV_RIGHT:
      car_turn_right();
      car_state = DEV_RIGHT;
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

void setup_drv8833() {
  // sets the pins as outputs:
  pinMode(motor_right_Pin1, OUTPUT);
  pinMode(motor_right_Pin2, OUTPUT);

  pinMode(motor_left_Pin1, OUTPUT);
  pinMode(motor_left_Pin2, OUTPUT);

  // configure LED PWM functionalitites
  ledcSetup(pwmChannel_motor_right_forward, freq, resolution);
  ledcAttachPin(motor_right_Pin1, pwmChannel_motor_right_forward);

  ledcSetup(pwmChannel_motor_left_forward, freq, resolution);
  ledcAttachPin(motor_left_Pin1, pwmChannel_motor_left_forward);

  ledcSetup(pwmChannel_motor_right_backward, freq, resolution);
  ledcAttachPin(motor_right_Pin2, pwmChannel_motor_right_backward);
  ledcSetup(pwmChannel_motor_left_backward, freq, resolution);
  ledcAttachPin(motor_left_Pin2, pwmChannel_motor_left_backward);
}

void loop_drv8833() {
}

#endif /* MOTOR_H */