
/* IR:  ESP32-C3
*/
#include <Arduino.h>
#include <IRremote.hpp>
#include "PinDefinitionsAndMore.h" // Define macros for input and output pin etc.
#include "stepper_motor.h"

#define DECODE_NEC // Includes Apple and Onkyo
#define IR_RECEIVE_PIN 13

// IR Remoter: ZTE
#define ACTION_LEFT 0x48
#define ACTION_RIGHT 0x4A
#define ACTION_UP 0x47
#define ACTION_DOWN 0x4B
#define ACTION_AUTO 0x49

int cur_ir_cmd;

void do_ir_cmd()
{
  switch (cur_ir_cmd)
  {
  case ACTION_LEFT:
    cur_cmd = DEV_LEFT;
    break;
  case ACTION_RIGHT:
    cur_cmd = DEV_RIGHT;
    break;
  case ACTION_UP:
    cur_cmd = DEV_UP;
    break;
  case ACTION_DOWN:
    cur_cmd = DEV_DOWN;
    break;
  case ACTION_AUTO:
    cur_cmd = DEV_AUTO;
    break;
  default:
    break;
  } // switch
  };

void setup_ir()
{

  Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));
  IrReceiver.begin(IR_RECEIVE_PIN, DISABLE_LED_FEEDBACK);
  Serial.print(F("Ready to receive IR signals of protocols: "));
  printActiveIRProtocols(&Serial);
  Serial.println(F("at pin " STR(ACTION_RECEIVE_PIN)));
}

void loop_ir()
{
  // IrReceiver
  if (IrReceiver.decode())
  {

    IrReceiver.printIRResultShort(&Serial);
    IrReceiver.printIRSendUsage(&Serial);
    if (IrReceiver.decodedIRData.protocol == UNKNOWN)
    {
      Serial.println(F("Received noise or an unknown (or not yet enabled) protocol"));
      IrReceiver.printIRResultRawFormatted(&Serial, true);
    }
    Serial.println();
    if (IrReceiver.decodedIRData.protocol != UNKNOWN)
    {
      cur_ir_cmd = IrReceiver.decodedIRData.command;
      do_ir_cmd();
    };                   // if
    IrReceiver.resume(); // Enable receiving of the next value
  };
}
