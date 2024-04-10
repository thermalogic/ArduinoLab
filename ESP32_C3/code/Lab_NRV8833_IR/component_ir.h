
/* IR:  ESP32-C3
*/
#include <Arduino.h>
#include <IRremote.hpp>
#include "PinDefinitionsAndMore.h" // Define macros for input and output pin etc.
#include "component_motor.h"

#define DECODE_NEC // Includes Apple and Onkyo
#define IR_RECEIVE_PIN 13

// IR Remoter: ZTE
#define ACTION_GO 0x47
#define ACTION_BACK 0x4B
#define ACTION_STOP 0x49
#define ACTION_LEFT 0x48
#define ACTION_RIGHT 0x4A

int get_ir_cmd(int cur_ir_code)
{
  int ir_cmd=DEV_STOP;
  switch (cur_ir_code)
  {
   case ACTION_GO:
    ir_cmd = DEV_GO;
    break;
  case ACTION_BACK:
    ir_cmd = DEV_BACK;
    break;
  case ACTION_LEFT:
    ir_cmd = DEV_LEFT;
    break;
  case ACTION_RIGHT:
    ir_cmd = DEV_RIGHT;
    break;
  case ACTION_STOP:
    ir_cmd = DEV_STOP;
    break;
  default:
    break;
  } // switch
  return ir_cmd;
  };

void setup_ir()
{
  Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));
  IrReceiver.begin(IR_RECEIVE_PIN, DISABLE_LED_FEEDBACK);
  Serial.print(F("Ready to receive IR signals of protocols: "));
  printActiveIRProtocols(&Serial);
  Serial.println(F("at pin " STR(ACTION_RECEIVE_PIN)));
}

void loop_ir_cmd()
{
  int ir_cmd=DEV_STOP;
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
       ir_cmd=get_ir_cmd(IrReceiver.decodedIRData.command);
       motor_action(ir_cmd);
    };                   // if
    IrReceiver.resume(); // Enable receiving of the next value
  };
}
