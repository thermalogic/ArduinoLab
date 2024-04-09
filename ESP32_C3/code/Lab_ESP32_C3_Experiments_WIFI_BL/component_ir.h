
/* SmallCar: ESP32
      IR
*/
#include <Arduino.h>
#include <IRremote.hpp>
#include "PinDefinitionsAndMore.h" // Define macros for input and output pin etc.
#include "component_dev.h"

#define DECODE_NEC // Includes Apple and Onkyo
#define IR_RECEIVE_PIN 13

#define ACTION_GO 0x47 // IR_Remoter: ZTE
#define ACTION_LEFT 0x48
#define ACTION_STOP 0x49
#define ACTION_RIGHT 0x4A
#define ACTION_BACK 0x4B

int cur_ir_cmd = ACTION_STOP;

void do_ir_cmd()
{
  switch (cur_ir_cmd)
  {
  case ACTION_GO:
    cur_cmd = DEV_GO;
    break;
  case ACTION_LEFT:
    cur_cmd = DEV_LEFT;
    break;
  case ACTION_RIGHT:
    cur_cmd = DEV_RIGHT;
    break;
  case ACTION_BACK:
    cur_cmd = DEV_BACK;
    break;
  case ACTION_STOP:
    cur_cmd = DEV_STOP;
    break;
  default:
    break;
  } // switch
  do_action();
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
