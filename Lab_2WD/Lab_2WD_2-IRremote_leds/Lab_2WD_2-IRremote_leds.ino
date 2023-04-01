
/*
 2WD IRmote Red
 */

#define DECODE_NEC  // Includes Apple and Onkyo

#define LED_Left 9
#define LED_Right 10
int brightness = 0;  // how bright the LED is ,fade for back

#include <Arduino.h>

#include "PinDefinitionsAndMore.h"  // Define macros for input and output pin etc.
#include <IRremote.hpp>

#define IR_RECEIVE_PIN 7 //IRremote.hpp  默认是pin2，小车使用pin11

void setup() {
  pinMode(LED_Left, OUTPUT);
  pinMode(LED_Right, OUTPUT);
  Serial.begin(115200);
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
    if (IrReceiver.decodedIRData.command == 0x11 || IrReceiver.decodedIRData.command == 0x18) {
      // forward - 2
      digitalWrite(LED_Left, HIGH);
      digitalWrite(LED_Right, HIGH);

    } else if (IrReceiver.decodedIRData.command == 0x14 || IrReceiver.decodedIRData.command == 0x8) {
      // Left - 4
      digitalWrite(LED_Left, HIGH);
      digitalWrite(LED_Right, LOW);

    } else if (IrReceiver.decodedIRData.command == 0x16 || IrReceiver.decodedIRData.command == 0x5A) {
      // right - 6
      digitalWrite(LED_Left, LOW);
      digitalWrite(LED_Right, HIGH);
    } else if (IrReceiver.decodedIRData.command == 0x19 || IrReceiver.decodedIRData.command == 0x52) {
      // back
      for (int i = 0; i < 3; i++) {
        digitalWrite(LED_Left, HIGH);
        digitalWrite(LED_Right, HIGH);
        delay(100);
        digitalWrite(LED_Left, LOW);
        digitalWrite(LED_Right, LOW);
        delay(100);
      };
      brightness =20;
      analogWrite(LED_Left, brightness);
      analogWrite(LED_Right, brightness);
    } else if (IrReceiver.decodedIRData.command == 0x15 || IrReceiver.decodedIRData.command == 0x1C) {
      // stop
      digitalWrite(LED_Left, LOW);
      digitalWrite(LED_Right, LOW);
    }
  }
}
