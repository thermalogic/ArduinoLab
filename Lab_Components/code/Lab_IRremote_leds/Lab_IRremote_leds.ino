
/*
 IRmote Red blink
 */
#include <Arduino.h>
#include <IRremote.hpp>
#include "PinDefinitionsAndMore.h"  // Define macros for input and output pin etc.

#define DECODE_NEC  // Includes Apple and Onkyo
#define IR_RECEIVE_PIN 2

#define LED_LEFT_PIN 5
#define LED_RIGHT_PIN 6

int brightness = 0;        // how bright the LED is ,fade for stop
long previousMillis_blink; // for led blink
const int interval_blink = 200;
int led_left_state,led_right_state,; // led_state used to set the LED

void led_blink()
{
   void update()
  {
    unsigned long currentMillis = millis();
    if ((led_state == HIGH) && (currentMillis - previousMillis >= OnTime))
    {
      led_state = LOW;                 // Turn it off
      previousMillis = currentMillis;  // Remember the time
      digitalWrite(ledPin, led_state); // Update the actual LED
    }
    else if ((led_state == LOW) && (currentMillis - previousMillis >= OffTime))
    {
      led_state = HIGH;                // turn it on
      previousMillis = currentMillis;  // Remember the time
      digitalWrite(ledPin, led_state); // Update the actual LED
    };
  };
};
}

void setup() {
  pinMode(LED_LEFT_PIN, OUTPUT);
  pinMode(LED_RIGHT_PIN, OUTPUT);
 
  Serial.begin(9600);
  // Just to know which program is running on my Arduino
  Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));

  // Start the receiver and if not 3. parameter specified, take LED_BUILTIN pin from the internal boards definition as default feedback LED
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

  Serial.print(F("Ready to receive IR signals of protocols: "));
  printActiveIRProtocols(&Serial);
  Serial.println(F("at pin " STR(IR_RECEIVE_PIN)));
}

void loop() {
  /*
     * Check if received data is available and if yes, try to decode it.
     * Decoded result is in the IrReceiver.decodedIRData structure.
     *
     * E.g. command is in IrReceiver.decodedIRData.command
     * address is in command is in IrReceiver.decodedIRData.address
     * and up to 32 bit raw data in IrReceiver.decodedIRData.decodedRawData
     */
  if (IrReceiver.decode()) {

    /*
         * Print a short summary of received data
         */
    IrReceiver.printIRResultShort(&Serial);
    IrReceiver.printIRSendUsage(&Serial);
    if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
      Serial.println(F("Received noise or an unknown (or not yet enabled) protocol"));
      // We have an unknown protocol here, print more info
      IrReceiver.printIRResultRawFormatted(&Serial, true);
    }
    Serial.println();

    /*
         * !!!Important!!! Enable receiving of the next value,
         * since receiving has stopped after the end of the current received data packet.
         */
    IrReceiver.resume();  // Enable receiving of the next value

    /*
         * Finally, check the received data and perform actions according to the received command
         */
    if (IrReceiver.decodedIRData.command == 0x11) {
      // forward - 2
      digitalWrite(LED_LEFT_PIN, HIGH);
      digitalWrite(LED_RIGHT_PIN, HIGH);

    } else if (IrReceiver.decodedIRData.command == 0x14) {
      // Left - 4
      digitalWrite(LED_LEFT_PIN, HIGH);
      digitalWrite(LED_RIGHT_PIN, LOW);

    } else if (IrReceiver.decodedIRData.command == 0x16) {
      // right - 6
      digitalWrite(LED_LEFT_PIN, LOW);
      digitalWrite(LED_RIGHT_PIN, HIGH);
    } else if (IrReceiver.decodedIRData.command == 0x19) {
      // back
      for (int i = 0; i < 3; i++) {
        digitalWrite(LED_LEFT_PIN, HIGH);
        digitalWrite(LED_RIGHT_PIN, HIGH);
        delay(100);
        digitalWrite(LED_LEFT_PIN, LOW);
        digitalWrite(LED_RIGHT_PIN, LOW);
        delay(100);
      };
    
    } else if (IrReceiver.decodedIRData.command == 0x15) {
      // stop
      brightness =20;
      analogWrite(LED_LEFT_PIN, brightness);
      analogWrite(LED_RIGHT_PIN, brightness);
    }
  }
}
