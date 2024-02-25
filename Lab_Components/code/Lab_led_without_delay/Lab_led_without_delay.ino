/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-led-blink-without-delay
 */

// constants won't change:
const int LED_PIN_1 = 3;            // the number of the LED 1 pin
const int LED_PIN_2 = LED_BUILTIN;  // the number of the LED 2 pin
const int BUTTON_PIN = 7;           // the number of the button pin

const long BLINK_INTERVAL_1 = 1000;  // interval at which to blink LED 1 (milliseconds)
const long BLINK_INTERVAL_2 = 500;   // interval at which to blink LED 2 (milliseconds)

// Variables will change:
int ledState_1 = LOW;   // ledState used to set the LED 1
int ledState_2 = LOW;   // ledState used to set the LED 2

int previousButtonState = LOW; // will store last time button was updated

unsigned long previousMillis_1 = 0;   // will store last time LED 1 was updated
unsigned long previousMillis_2 = 0;   // will store last time LED 2 was updated

void setup() {
  Serial.begin(9600);

  // set the digital pin as output:
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  
  // set the digital pin as an input:
  pinMode(BUTTON_PIN, INPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  // check to see if it's time to blink the LED 1
  if (currentMillis - previousMillis_1 >= BLINK_INTERVAL_1) {
    // if the LED is off turn it on and vice-versa:
    ledState_1 = (ledState_1 == LOW) ? HIGH : LOW;

    // set the LED with the ledState of the variable:
    digitalWrite(LED_PIN_1, ledState_1);

    // save the last time you blinked the LED
    previousMillis_1 = currentMillis;
  }

  // check to see if it's time to blink the LED 2
  if (currentMillis - previousMillis_2 >= BLINK_INTERVAL_2) {
    // if the LED is off turn it on and vice-versa:
    ledState_2 = (ledState_2 == LOW) ? HIGH : LOW;

    // set the LED with the ledState of the variable:
    digitalWrite(LED_PIN_2, ledState_2);

    // save the last time you blinked the LED
    previousMillis_2 = currentMillis;
  }

  // check button state's change
  int currentButtonState = digitalRead(BUTTON_PIN);

  if(currentButtonState != previousButtonState) {
    // print out the state of the button:
    Serial.println(currentButtonState);

    // save the last state of button
    previousButtonState = currentButtonState;
  }

  // DO OTHER WORKS HERE
}