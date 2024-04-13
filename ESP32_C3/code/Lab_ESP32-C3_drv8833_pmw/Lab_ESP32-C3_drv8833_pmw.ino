/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-dc-motor-l298n-motor-driver-control-speed-direction/
*********/


// Motor A Right OK!
int motor1Pin1 = 1;  //AIN1绿色
int motor1Pin2 = 0;  //AIN2黄色


// Motor B
int motor2Pin1 = 3;   //  BIN1 绿色
int motor2Pin2 = 10;  // BIN2 黄色

// Setting PWM properties
const int freq = 30000;
const int pwmChannel_motor1 = 0;
const int pwmChannel_motor2 = 1;
const int resolution = 8;
int dutyCycle = 200;


// motor action code
const int DEV_GO = 1;
const int DEV_BACK = 2;
const int DEV_LEFT = 3;
const int DEV_RIGHT = 4;
const int DEV_STOP = 5;

// PWM - speed
const int left_speed = 200;
const int right_speed = 200;
const int turn_speed_diff = 120;

int i=0;

void car_forward() {
  // Moving Forward
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  ledcWrite(pwmChannel_motor1, left_speed);

  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  ledcWrite(pwmChannel_motor2, right_speed);
}

void car_forward_speedup() {
  // Move DC motor forward with increasing speed
  dutyCycle = 200;
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  while (dutyCycle <= 255) {
    ledcWrite(pwmChannel_motor1, dutyCycle);
    Serial.println(dutyCycle);
    dutyCycle = dutyCycle + 5;
    delay(500);
  }
}

void car_back() {
  // Move DC motor backwards at maximum speed
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);

  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
}

void car_stop() {
  // Stop the DC motor
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  ledcWrite(pwmChannel_motor1, 0);
  ledcWrite(pwmChannel_motor2, 0);
}

void car_turn_left() {
}

void car_turn_right() {
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
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);

  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);

  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);

  // configure LED PWM functionalitites
  ledcSetup(pwmChannel_motor1, freq, resolution);
  ledcAttachPin(motor1Pin1, pwmChannel_motor1);


  ledcSetup(pwmChannel_motor2, freq, resolution);
  ledcAttachPin(motor2Pin1, pwmChannel_motor2);

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

    //car_stop();
    //delay(2000);

    //car_back();
    //delay(1000);

    car_stop();
    delay(1000);
    i++;
  }
}