
/*
 IRmote Red blink
 */
#include <Arduino.h>
#include <IRremote.hpp>
#include "PinDefinitionsAndMore.h"  // Define macros for input and output pin etc.

#define DECODE_NEC  // Includes Apple and Onkyo
#define ACTION_RECEIVE_PIN 2

#define LED_LEFT_PIN 5
#define LED_RIGHT_PIN 6

int brightness = 0;         // how bright the LED is ,fade for DEV_STOP
long previousMillis_blink;  // for led blink
const int interval_blink = 200;
int led_left_state, led_right_state;  // led_state used to set the LED

#define ACTION_GO 0x47 //ZTE
#define ACTION_LEFT 0x48
#define ACTION_STOP 0x49
#define ACTION_RIGHT 0x4A
#define ACTION_BACK 0x4B

int state = ACTION_STOP;

int update_led_state(int led_pin, int led_state) {
  if (led_state == LOW) {
    led_state = HIGH;
  } else {
    led_state = LOW;
  };
  digitalWrite(led_pin, led_state);  // Update the LED
  return led_state;
}

void led_blink() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis_blink >= interval_blink) {
    previousMillis_blink = currentMillis;  // Remember the time
    led_left_state = update_led_state(LED_LEFT_PIN, led_left_state);
    led_right_state = update_led_state(LED_RIGHT_PIN, led_right_state);
  };
};

void setup() {
  pinMode(LED_LEFT_PIN, OUTPUT);
  pinMode(LED_RIGHT_PIN, OUTPUT);
  brightness = 20;
  analogWrite(LED_LEFT_PIN, brightness);
  analogWrite(LED_RIGHT_PIN, brightness);

  Serial.begin(9600);
  Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));
  IrReceiver.begin(ACTION_RECEIVE_PIN,  DISABLE_LED_FEEDBACK);
  Serial.print(F("Ready to receive IR signals of protocols: "));
  printActiveIRProtocols(&Serial);
  Serial.println(F("at pin " STR(ACTION_RECEIVE_PIN)));
}

void loop() {
  if (state == ACTION_BACK) {
    led_blink();
  }
  if (IrReceiver.decode()) {

    IrReceiver.printIRResultShort(&Serial);
    IrReceiver.printIRSendUsage(&Serial);
    if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
      Serial.println(F("Received noise or an unknown (or not yet enabled) protocol"));
      IrReceiver.printIRResultRawFormatted(&Serial, true);
    }
    Serial.println();

    IrReceiver.resume();  // Enable receiving of the next value

    if (IrReceiver.decodedIRData.command == ACTION_GO) {
      state = ACTION_GO;
      digitalWrite(LED_LEFT_PIN, HIGH);
      digitalWrite(LED_RIGHT_PIN, HIGH);

    } else if (IrReceiver.decodedIRData.command ==  ACTION_LEFT) {
      // DEV_LEFT - 4
      state = ACTION_LEFT;
      digitalWrite(LED_LEFT_PIN, HIGH);
      digitalWrite(LED_RIGHT_PIN, LOW);
    } else if (IrReceiver.decodedIRData.command == ACTION_RIGHT) {
      // right - 6
      state = ACTION_RIGHT;
      digitalWrite(LED_LEFT_PIN, LOW);
      digitalWrite(LED_RIGHT_PIN, HIGH);
    } else if (IrReceiver.decodedIRData.command == ACTION_BACK) {
      state = ACTION_BACK;
      previousMillis_blink = 0;
      led_left_state = LOW;
      led_right_state = LOW;
      digitalWrite(LED_LEFT_PIN, led_left_state);
      digitalWrite(LED_RIGHT_PIN, led_right_state);
    } else if (IrReceiver.decodedIRData.command ==  ACTION_STOP) {
      state = ACTION_STOP;
      brightness = 20;
      analogWrite(LED_LEFT_PIN, brightness);
      analogWrite(LED_RIGHT_PIN, brightness);
    }
  }
}
