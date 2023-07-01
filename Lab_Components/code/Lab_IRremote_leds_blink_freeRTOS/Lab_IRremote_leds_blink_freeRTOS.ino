
/*

FreeRTOS: IRmote Red blink
多任务后，红外信号解析不可靠
*/
#include <Arduino_FreeRTOS.h>
#include <IRremote.hpp>
#include "PinDefinitionsAndMore.h"  // Define macros for input and output pin etc.

#define DECODE_NEC  // Includes Apple and Onkyo
#define IR_RECEIVE_PIN 2

#define LED_LEFT_PIN 5
#define LED_RIGHT_PIN 6

#define ACTION_GO 0x47  //ZTE
#define ACTION_LEFT 0x48
#define ACTION_STOP 0x49
#define ACTION_RIGHT 0x4A
#define ACTION_BACK 0x4B

int brightness = 0;  // how bright the LED is ,fade for ACTION_STOP
int cur_action = ACTION_STOP;

void TaskReadIR(void *pvParameters) {
  (void)pvParameters;
  Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));
  IrReceiver.begin(IR_RECEIVE_PIN, DISABLE_LED_FEEDBACK);
  Serial.print(F("Ready to receive IR signals of protocols: "));
  printActiveIRProtocols(&Serial);
  Serial.println(F("at pin " STR(ACTION_RECEIVE_PIN)));

  for (;;)  
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
      if (IrReceiver.decodedIRData.protocol != UNKNOWN & IrReceiver.decodedIRData.command != cur_action) {
        cur_action = IrReceiver.decodedIRData.command;
        switch (cur_action) {
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
            digitalWrite(LED_LEFT_PIN, LOW);
            digitalWrite(LED_RIGHT_PIN, LOW);
            break;
          case ACTION_STOP:
            brightness = 20;
            analogWrite(LED_LEFT_PIN, brightness);
            analogWrite(LED_RIGHT_PIN, brightness);
            break;
          default:
            break;
        }
      }
    }
  }
}

void TaskBlink(void *pvParameters)  // This is a task.
{
  (void)pvParameters;
  for (;;) {
    if (cur_action == ACTION_BACK) {
     //   digitalWrite(LED_LEFT_PIN, HIGH);
     //  digitalWrite(LED_RIGHT_PIN, HIGH);
       vTaskDelay(1000 / portTICK_PERIOD_MS);  // wait for one second
    //  digitalWrite(LED_LEFT_PIN, LOW);
    //  digitalWrite(LED_RIGHT_PIN, LOW);
      vTaskDelay(1000 / portTICK_PERIOD_MS);  // wait for one second
   
    };
  }
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
    TaskReadIR, "ReadIR",
    128  // Stack size
    ,
    NULL, 3  // Priority
    ,
    NULL);

  /*xTaskCreate(
    TaskBlink, "Blink"  // A name just for humans
    ,
    128  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,
    NULL, 3  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,
    NULL);
*/
  
}

void loop() {
}
