
/*
  Led
*/
#ifndef LED_H
#define LED_H

#include "component_btn7919.h"
#include <Arduino.h>

#define LED_LEFT_PIN 12
#define LED_RIGHT_PIN 23

// int led_brightness;        // how bright the LED is ,fade for STOP
long previousMillis_blink; // for led blink
const int interval_blink = 200;
int led_left_cur_action, led_right_cur_action; // led_cur_action used to set the LED

int update_led_cur_action(int led_pin, int led_cur_action)
{
  if (led_cur_action == LOW)
  {
    led_cur_action = HIGH;
  }
  else
  {
    led_cur_action = LOW;
  };
  digitalWrite(led_pin, led_cur_action); // Update the LED
  return led_cur_action;
}

void led_blink()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis_blink >= interval_blink)
  {
    previousMillis_blink = currentMillis; // Remember the time
    led_left_cur_action = update_led_cur_action(LED_LEFT_PIN, led_left_cur_action);
    led_right_cur_action = update_led_cur_action(LED_RIGHT_PIN, led_right_cur_action);
  };
};

void setup_led()
{
  pinMode(LED_LEFT_PIN, OUTPUT);
  pinMode(LED_RIGHT_PIN, OUTPUT);
  // led_brightness = 20;
  // analogWrite(LED_LEFT_PIN, led_brightness);
  // analogWrite(LED_RIGHT_PIN, led_brightness);
  digitalWrite(LED_LEFT_PIN, HIGH);
  digitalWrite(LED_RIGHT_PIN, HIGH);
}

void led_action(int cur_cmd)
{
  switch (cur_cmd)
  {
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
    // led_brightness = 20;
    digitalWrite(LED_LEFT_PIN, HIGH);
    digitalWrite(LED_RIGHT_PIN, HIGH);
    // digitalWrite(LED_LEFT_PIN, LOW);
    // digitalWrite(LED_RIGHT_PIN, LOW);
    //  analogWrite(LED_LEFT_PIN, led_brightness);
    // analogWrite(LED_RIGHT_PIN, led_brightness);
    break;
  default:
    break;
  }
};

void loop_led()
{
  if (car_state == DEV_BACK)
  {
    led_blink();
  };
}

#endif /* LED_H */