
/*
FreeRTOS: IRmote Red blink

  while(state == DEV_BACK) {  // state的改变没有体现在这个task ,state需要修改为信号量？
 */
#include <Arduino_FreeRTOS.h>
#include <IRremote.hpp>
#include "PinDefinitionsAndMore.h"  // Define macros for input and output pin etc.

#define DECODE_NEC  // Includes Apple and Onkyo
#define IR_RECEIVE_PIN 2

#define LED_LEFT_PIN 5
#define LED_RIGHT_PIN 6

int brightness = 0;         // how bright the LED is ,fade for DEV_STOP

#define DEV_GO 0
#define DEV_BACK 1
#define DEV_STOP 2
#define DEV_LEFT 3
#define DEV_RIGHT 4

#define IR_GO 0x47  //ZTE
#define IR_LEFT 0x48
#define IR_STOP 0x49
#define IR_RIGHT 0x4A
#define IR_BACK 0x4B


int state = DEV_STOP;

// define two tasks for Blink & ReadIR
void TaskReadIR(void *pvParameters);
void TaskBlink(void *pvParameters);

void TaskReadIR(void *pvParameters) {
  (void)pvParameters;
  Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));
  IrReceiver.begin(IR_RECEIVE_PIN, DISABLE_LED_FEEDBACK);
  Serial.print(F("Ready to receive IR signals of protocols: "));
  printActiveIRProtocols(&Serial);
  Serial.println(F("at pin " STR(IR_RECEIVE_PIN)));
  
  for (;;)  // A Task shall never return or exit.
  {
    if (IrReceiver.decode()) {

      IrReceiver.printIRResultShort(&Serial);
      IrReceiver.printIRSendUsage(&Serial);
      if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
        Serial.println(F("Received noise or an unknown (or not yet enabled) protocol"));
        IrReceiver.printIRResultRawFormatted(&Serial, true);
      }
      Serial.println();

      IrReceiver.resume();  // Enable receiving of the next value

      if (IrReceiver.decodedIRData.command == IR_GO) {
        state = DEV_GO;
        digitalWrite(LED_LEFT_PIN, HIGH);
        digitalWrite(LED_RIGHT_PIN, HIGH);

      } else if (IrReceiver.decodedIRData.command == IR_LEFT) {
        state = DEV_LEFT;
        digitalWrite(LED_LEFT_PIN, HIGH);
        digitalWrite(LED_RIGHT_PIN, LOW);
      } else if (IrReceiver.decodedIRData.command == IR_RIGHT) {
        state = DEV_RIGHT;
        digitalWrite(LED_LEFT_PIN, LOW);
        digitalWrite(LED_RIGHT_PIN, HIGH);
      } else if (IrReceiver.decodedIRData.command == IR_BACK) {
        state = DEV_BACK; 
        digitalWrite(LED_LEFT_PIN, LOW);
        digitalWrite(LED_RIGHT_PIN, LOW);
      } else if (IrReceiver.decodedIRData.command == IR_STOP) {
        state = DEV_STOP;
        brightness = 20;
        analogWrite(LED_LEFT_PIN, brightness);
        analogWrite(LED_RIGHT_PIN, brightness);
      }
    }
  }
}

void TaskBlink(void *pvParameters)  // This is a task.
{
  (void)pvParameters;
  while(state == DEV_BACK) {  // state的改变没有体现在这个task ,state需要修改为信号量？
      digitalWrite(LED_LEFT_PIN, LOW);
      digitalWrite(LED_RIGHT_PIN, LOW);
      vTaskDelay(1000 / portTICK_PERIOD_MS);  // wait for one second
      digitalWrite(LED_LEFT_PIN, HIGH);
      digitalWrite(LED_RIGHT_PIN, HIGH);
      vTaskDelay(1000 / portTICK_PERIOD_MS);  // wait for one second
   };
};

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;  // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
  }

  pinMode(LED_LEFT_PIN, OUTPUT);
  pinMode(LED_RIGHT_PIN, OUTPUT);
  brightness = 20;
  analogWrite(LED_LEFT_PIN, brightness);
  analogWrite(LED_RIGHT_PIN, brightness);
  
   xTaskCreate(
    TaskReadIR, "ReadIR"
    , 
    128  // Stack size
    ,
    NULL, 2  // Priority
    ,
    NULL);

  xTaskCreate(
    TaskBlink, "Blink"  // A name just for humans
    ,
    128  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,
    NULL, 1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,
    NULL);  

}

void loop() {
}
