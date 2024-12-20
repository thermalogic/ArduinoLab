/*

*/


// Motor A Right OK!
int motor_right_Pin1 = 1;  //AIN1绿色
int motor_right_Pin2 = 0;  //AIN2黄色

// Motor B left
int motor_left_Pin1 = 3;   //  BIN1 绿色
int motor_left_Pin2 = 10;  // BIN2 黄色

// Setting PWM properties
const int freq = 30000;
const int pwmChannel_motor_right_forward= 0;
const int pwmChannel_motor_left_forward= 1;
const int resolution = 8;
int dutyCycle = 200;


// motor action code
const int DEV_GO = 1;
const int DEV_BACK = 2;
const int DEV_LEFT = 3;
const int DEV_RIGHT = 4;
const int DEV_STOP = 5;

// PWM - speed
int left_speed = 200;
int right_speed = 200;
const int turn_speed_diff = 120;
const int speed_step = 30;

int i = 0;

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
  ledcWrite(pwmChannel_motor_right_forward, 100);

  digitalWrite(motor_left_Pin1, LOW);
  digitalWrite(motor_left_Pin2, HIGH);
  ledcWrite(pwmChannel_motor_left_forward, 100);
}

void car_stop() {
  // Stop the DC motor
  digitalWrite(motor_right_Pin1, LOW);
  digitalWrite(motor_right_Pin2, LOW);
  ledcWrite(pwmChannel_motor_left_forward, 0);
  ledcWrite(pwmChannel_motor_right_forward, 0);
}

void car_turn_left() {
  // turn_left
  digitalWrite(motor_right_Pin1, HIGH);
  digitalWrite(motor_right_Pin2, LOW);
  ledcWrite(pwmChannel_motor_right_forward, right_speed);

  digitalWrite(motor_left_Pin1, HIGH);
  digitalWrite(motor_left_Pin2, LOW);
  left_speed = right_speed - turn_speed_diff;
  if (left_speed < 0) {
    left_speed = 0;
  }
  ledcWrite(pwmChannel_motor_left_forward, left_speed);
}

void car_turn_right() {
  // turn right
  digitalWrite(motor_left_Pin1, HIGH);
  digitalWrite(motor_left_Pin2, LOW);
  left_speed=200;
  ledcWrite(pwmChannel_motor_left_forward, left_speed);

  digitalWrite(motor_right_Pin1, HIGH);
  digitalWrite(motor_right_Pin2, LOW);
  right_speed = left_speed - turn_speed_diff;
  if (right_speed < 0) {
    right_speed = 0;
  }
  ledcWrite(pwmChannel_motor_right_forward,right_speed);
}

void car_speedup() {
  right_speed += speed_step;
  if (right_speed > 255) {
    right_speed = 255;
  }
  ledcWrite(pwmChannel_motor_right_forward, right_speed);

  left_speed += speed_step;
  if (left_speed > 255) {
    left_speed = 255;
  }
  ledcWrite(pwmChannel_motor_left_forward, left_speed);
}

void car_speeddown() {
  right_speed -= speed_step;
  if (right_speed <0) {
    right_speed = 0;
  }
  ledcWrite(pwmChannel_motor_right_forward, right_speed);

  left_speed -= speed_step;
  if (left_speed <0 ) {
    left_speed = 0;
  }
  ledcWrite(pwmChannel_motor_left_forward, left_speed);
}

void car_action(int car_cmd) {
  switch (car_cmd) {
    case DEV_GO:
      car_forward();
      break;
    case DEV_LEFT:
      car_turn_left();
      break;
    case DEV_RIGHT:
      car_turn_right();
      break;
    case DEV_BACK:
      car_back();
      break;
    case DEV_STOP:
      car_stop();
      break;
    default:
      break;
  }  // switch
};

void setup() {
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

  Serial.begin(115200);
  // testing
  Serial.print("Testing DC Motor...");

  delay(2000);

  i = 0;
}


void loop() {
  // forward
  while (i < 2) {
    car_forward();
    delay(2000);

    car_speeddown();
    delay(2000);
    
    car_speedup();
    delay(2000);
    
    car_back();
    delay(2000);

    car_turn_left();
    delay(2000);

    car_turn_right();
    delay(2000);

    car_stop();
    delay(1000);
    i++;
  }
}