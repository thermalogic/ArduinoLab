/*
 * LAB Name: Exchange Data Over Bluetooth
 *      Android SmartPhone <-> ESP32 Bluetooth
 *      Laptop Serial BT   <-> ESP32 Bluetooth
 */
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

// Bluetooth Serial Object (Handle)
BluetoothSerial SerialBT;
// Timer0 configuration Handle
hw_timer_t *Timer0_Cfg = NULL;

// ESP32 Bluetooth (Slave) Device Information
const char *pin = "1234"; // Change this to more secure PIN.
String device_name = "ESP32-BT-Slave";

// Bluetooth Received Byte & Message Buffer Array
String RxBuffer = "";
char RxByte;

// Timer0 ISR Handler Function (Configured To Execute Every 1000ms)
void IRAM_ATTR Timer0_ISR()
{
  SerialBT.println(Temperature);
  SerialBT.println(Humidity);
  SerialBT.println(distance);
}

void setup_bluetooth()
{
  SerialBT.begin(device_name); // Bluetooth device name
  // Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());
  SerialBT.setPin(pin);
  Serial.println("Using PIN");

  // Configure Timer0 Interrupt (Every 1000mS)
  Timer0_Cfg = timerBegin(0, 80, true);
  timerAttachInterrupt(Timer0_Cfg, &Timer0_ISR, true);
  timerAlarmWrite(Timer0_Cfg, 1000000, true);
  timerAlarmEnable(Timer0_Cfg);
}

void loop_bluetooth()
{
  // Read The Received Bytes & Add Them To Message (RxBuffer) Array
  if (SerialBT.available())
  {
    RxByte = SerialBT.read();
    if (RxByte != '\n')
    {
      RxBuffer += String(RxByte);
    }
    else
    {
      RxBuffer = "";
    }
    Serial.write(RxByte);
  }
  // Check The Received Message & Update Output LED State
  if (RxBuffer == "go")
  {
    cur_cmd = DEV_GO;
  }
  else if (RxBuffer == "back")
  {
    cur_cmd = DEV_BACK;
  }
  else if (RxBuffer == "left")
  {
    cur_cmd = DEV_LEFT;
  }
  else if (RxBuffer == "right")
  {
    cur_cmd = DEV_RIGHT;
  }
  else if (RxBuffer == "stop")
  {
    cur_cmd = DEV_STOP;
  };
  do_action();
}