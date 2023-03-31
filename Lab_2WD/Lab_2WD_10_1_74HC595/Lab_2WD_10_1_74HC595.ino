int latchPin = 3;  // Latch pin of 74HC595 is connected to Digital pin 3
int clockPin = 4;  // Clock pin of 74HC595 is connected to Digital pin 4
int dataPin = 2;   // Data pin of 74HC595 is connected to Digital pin 2

byte values = 0;  // Variable to hold the pattern of which LEDs are currently turned on or off

// 74hc595
#define MOTOR_LEFT_FORWARD 1
#define MOTOR_LEFT_BACK 2
#define MOTOR_RIGHT_FORWARD 3
#define MOTOR_RIGHT_BACK 4
#define LED_LEFT 5
#define LED_RIGHT 6
//arduino
#define leftPWM 5
#define rightPWM 6

#define MOTOR_GO 0
#define MOTOR_BACK 1
#define MOTOR_STOP 2
#define MOTOR_LEFT 3
#define MOTOR_RIGHT 4

int speed_level1 = 100;  // 转向时用，转速差，转向
int speed_level2 = 200;  // 太低驱动不了，调试后200，比较合适
int speed_level3 = 255;

int motor_state = MOTOR_STOP;
int motor_cmd = MOTOR_STOP;

long previousMillis;

void updateShiftRegister() {
  //
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, values);
  digitalWrite(latchPin, HIGH);
};

void motor_init() {
  // 默认停止状态
  analogWrite(leftPWM, 0);
  analogWrite(rightPWM, 0);
  // 默认全是低电平 停止状态
  bitClear(values, 7 - MOTOR_LEFT_FORWARD);
  bitClear(values, 7 - MOTOR_LEFT_BACK);
  bitClear(values, 7 - MOTOR_RIGHT_FORWARD);
  bitClear(values, 7 - MOTOR_RIGHT_BACK);
  updateShiftRegister();
}

void motor_go() {
  // 左轮前进
  analogWrite(leftPWM, speed_level2);
  bitSet(values, 7 - MOTOR_LEFT_FORWARD);
  bitClear(values, 7 - MOTOR_LEFT_BACK);
  // 右轮前进
  analogWrite(rightPWM, speed_level2);
  bitSet(values, 7 - MOTOR_RIGHT_FORWARD);
  bitClear(values, 7 - MOTOR_RIGHT_BACK);
}

void motor_back() {
  analogWrite(leftPWM, speed_level2);
  // 左轮后退
  bitClear(values, 7 - MOTOR_LEFT_FORWARD);
  bitSet(values, 7 - MOTOR_LEFT_BACK);
  // 右轮后退;
  analogWrite(rightPWM, speed_level2);
  bitClear(values, 7 - MOTOR_RIGHT_FORWARD);
  bitSet(values, 7 - MOTOR_RIGHT_BACK);
}

void motor_turn_left() {
  // 左轮低速
  analogWrite(leftPWM, speed_level1);
  bitSet(values, 7 - MOTOR_LEFT_FORWARD);
  bitClear(values, 7 - MOTOR_LEFT_BACK);
  // 右轮前进
  analogWrite(rightPWM, speed_level2);
  bitSet(values, 7 - MOTOR_RIGHT_FORWARD);
  bitClear(values, 7 - MOTOR_RIGHT_BACK);
}

void motor_turn_right() {
  // 左轮前进
  analogWrite(leftPWM, speed_level2);
  bitSet(values, 7 - MOTOR_LEFT_FORWARD);
  bitClear(values, 7 - MOTOR_LEFT_BACK);
  // 右轮低速
  analogWrite(rightPWM, speed_level1);
  bitSet(values, 7 - MOTOR_RIGHT_FORWARD);
  bitClear(values, 7 - MOTOR_RIGHT_BACK);
}

void motor_stop() {
  motor_init();
}


void motor_action(int motor_cmd) {
  switch (motor_cmd) {
    case MOTOR_GO:
      //led_left.on(values);
      //led_right.on(values);
      bitSet(values, 7 - LED_LEFT);
      bitSet(values, 7 - LED_RIGHT);
      motor_go();
      updateShiftRegister();
      motor_state = motor_cmd;
      break;
    case MOTOR_STOP:
      //led_left.off(values);
      //led_right.off(values);
      bitClear(values, 7 - LED_LEFT);
      bitClear(values, 7 - LED_RIGHT);
      motor_stop();
      updateShiftRegister();
      motor_state = motor_cmd;
      break;
    case MOTOR_BACK:
      previousMillis = 0;
      motor_back();
      updateShiftRegister();
      motor_state = motor_cmd;
      break;
    case MOTOR_LEFT:
      bitSet(values, 7 - LED_LEFT);
      bitClear(values, 7 - LED_RIGHT);
      motor_turn_left();
      updateShiftRegister();
      motor_state = motor_cmd;
      break;
    case MOTOR_RIGHT:
      bitClear(values, 7 - LED_LEFT);
      bitSet(values, 7 - LED_RIGHT);
      motor_turn_right();
      updateShiftRegister();
      motor_state = motor_cmd;
      break;
    default:
      break;
  };
};

void setup() {
  Serial.begin(9600);
  // Set all the pins of 74HC595 as OUTPUT
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  updateShiftRegister();
  motor_init();
}

void loop() {

  if (motor_state == MOTOR_BACK) {
    unsigned long currentMillis = millis();
    if ((bitRead(values, 7 - LED_LEFT) == 1) && (currentMillis - previousMillis >= 200)) {
      previousMillis = currentMillis;  // Remember the time
      bitClear(values, 7 - LED_LEFT);
      bitClear(values, 7 - LED_RIGHT);
      updateShiftRegister();
    } else if ((bitRead(values, 7 - LED_LEFT) == 0) && (currentMillis - previousMillis >= 200)) {
      previousMillis = currentMillis;  // Remember the time
      bitSet(values, 7 - LED_LEFT);
      bitSet(values, 7 - LED_RIGHT);
      updateShiftRegister();
    };
  };
  motor_cmd = MOTOR_BACK;
  //motor_action(MOTOR_GO);
  //delay(2000);
  if (motor_cmd != motor_state) {
    motor_action(MOTOR_BACK);
  };
  //delay(2000);
  //motor_action(MOTOR_LEFT);
  // delay(2000);
  // motor_action(MOTOR_RIGHT);
  // delay(2000);
  //  motor_action(MOTOR_STOP);
  // delay(2000);
}
