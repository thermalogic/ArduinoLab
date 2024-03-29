
/*
 IR remote Led blink
 ESP32
 */
#include <Arduino.h>
#include <IRremote.hpp>
#include "PinDefinitionsAndMore.h"  // Define macros for input and output pin etc.

#define DECODE_NEC  // Includes Apple and Onkyo
#define IR_RECEIVE_PIN  19

#define LED_LEFT_PIN 18
#define LED_RIGHT_PIN 5

#define ACTION_GO 0x47  // IR_Remoter: ZTE
#define ACTION_LEFT 0x48
#define ACTION_STOP 0x49
#define ACTION_RIGHT 0x4A
#define ACTION_BACK 0x4B

int led_brightness;         // how bright the LED is ,fade for ACTION_STOP
long previousMillis_blink;  // for led blink
const int interval_blink = 200;
int led_left_cur_action, led_right_cur_action;  // led_cur_action used to set the LED

int dev_cur_action = ACTION_STOP;

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

void setup() {
  pinMode(LED_LEFT_PIN, OUTPUT);
  pinMode(LED_RIGHT_PIN, OUTPUT);
  led_brightness = 20;
  analogWrite(LED_LEFT_PIN, led_brightness);
  analogWrite(LED_RIGHT_PIN, led_brightness);

  Serial.begin(9600);
  Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));
  IrReceiver.begin(IR_RECEIVE_PIN, DISABLE_LED_FEEDBACK);
  Serial.print(F("Ready to receive IR signals of protocols: "));
  printActiveIRProtocols(&Serial);
  Serial.println(F("at pin " STR(ACTION_RECEIVE_PIN)));
}

void loop() {
  if (dev_cur_action == ACTION_BACK) {
    led_blink();
  }
  // IrReceiver
  if (IrReceiver.decode()) {

    IrReceiver.printIRResultShort(&Serial);
    IrReceiver.printIRSendUsage(&Serial);
    if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
      Serial.println(F("Received noise or an unknown (or not yet enabled) protocol"));
      IrReceiver.printIRResultRawFormatted(&Serial, true);
    }
    Serial.println();

    IrReceiver.resume();  // Enable receiving of the next value
    if (IrReceiver.decodedIRData.protocol != UNKNOWN & IrReceiver.decodedIRData.command != dev_cur_action) {
      dev_cur_action = IrReceiver.decodedIRData.command;
      switch (dev_cur_action) {
        case ACTION_GO:
          digitalWrite(LED_LEFT_PIN, HIGH);
          digitalWrite(LED_RIGHT_PIN, HIGH);
          break;
        case ACTION_LEFT:
          digitalWrite(LED_LEFT_PIN, HIGH);
          digitalWrite(LED_RIGHT_PIN, LOW);
          break;
        case ACTION_RIGHT:
          digitalWrite(LED_LEFT_PIN, LOW);
          digitalWrite(LED_RIGHT_PIN, HIGH);
          break;
        case ACTION_BACK:
          previousMillis_blink = 0;
          led_left_cur_action = LOW;
          led_right_cur_action = LOW;
          digitalWrite(LED_LEFT_PIN, led_left_cur_action);
          digitalWrite(LED_RIGHT_PIN, led_right_cur_action);
          break;
        case ACTION_STOP:
          led_brightness = 20;
          analogWrite(LED_LEFT_PIN, led_brightness);
          analogWrite(LED_RIGHT_PIN, led_brightness);
          break;
        default:
          break;
      }  //switch
    };   //if
  };
}
