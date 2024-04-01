
/* SmallCar: ESP32 
     Device - LED
*/
#ifndef DEVICE_H
#define DEVICE_H

#define LED_LEFT_PIN 18
#define LED_RIGHT_PIN 5

// Device action code
const int DEV_GO = 1;
const int DEV_BACK = 2;
const int DEV_STOP = 3;
const int DEV_LEFT = 4;
const int DEV_RIGHT = 5;
const int DEV_UP = 6;
const int DEV_DOWN = 7;

long previousMillis_blink;  // for led blink
const int interval_blink = 200;
int led_left_cur_action, led_right_cur_action;  // led_cur_action used to set the LED

int cur_cmd = DEV_STOP;

int update_led_cur_action(int led_pin, int led_cur_action) {
  if (led_cur_action == LOW) {
    led_cur_action = HIGH;
  } else {
    led_cur_action = LOW;
  };
  digitalWrite(led_pin, led_cur_action);  // Update the LED
  return led_cur_action;
}

void led_blink() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis_blink >= interval_blink) {
    previousMillis_blink = currentMillis;  // Remember the time
    led_left_cur_action = update_led_cur_action(LED_LEFT_PIN, led_left_cur_action);
    led_right_cur_action = update_led_cur_action(LED_RIGHT_PIN, led_right_cur_action);
  };
};

void do_action() {
  switch (cur_cmd) {
    case DEV_GO:
      digitalWrite(LED_LEFT_PIN, HIGH);
      digitalWrite(LED_RIGHT_PIN, HIGH);
      break;
    case DEV_LEFT:
      digitalWrite(LED_LEFT_PIN, HIGH);
      digitalWrite(LED_RIGHT_PIN, LOW);
      break;
    case DEV_RIGHT:
      digitalWrite(LED_LEFT_PIN, LOW);
      digitalWrite(LED_RIGHT_PIN, HIGH);
      break;
    case DEV_BACK:
      previousMillis_blink = 0;
      led_left_cur_action = LOW;
      led_right_cur_action = LOW;
      digitalWrite(LED_LEFT_PIN, led_left_cur_action);
      digitalWrite(LED_RIGHT_PIN, led_right_cur_action);
      break;
    case DEV_STOP:
      digitalWrite(LED_LEFT_PIN, LOW);
      digitalWrite(LED_RIGHT_PIN, LOW);
      break;
    default:
      break;
  }  // switch
};

void setup_dev() {
  pinMode(LED_LEFT_PIN, OUTPUT);
  pinMode(LED_RIGHT_PIN, OUTPUT);
  cur_cmd = DEV_STOP;
 }

void loop_dev() {
  if (cur_cmd == DEV_BACK) {
     led_blink();
  }
}

#endif /* DEVICE_H */