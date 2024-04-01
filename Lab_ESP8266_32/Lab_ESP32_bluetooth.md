# ESP蓝牙控制

ESP蓝牙控制：`Lab_ESP32_Experiments_bluetooth.ino`,通过

* ESP32 Bluetooth Classic With Arduino – Complete Guide
  * https://deepbluembedded.com/esp32-bluetooth-classic-with-arduino-complete-guide/

* 手机端软件： “Serial Bluetooth Terminal”

## ESP32 Bluetooth With Android Smartphone (RX)

The ESP32 Bluetooth Receiver will Turn ON and OFF an LED based on the received string of data 

that will be sent from the Smartphone over Bluetooth communication.

上载代码到ESP32后， clicking the `EN` button on the ESP32 board after a new firmware (sketch) is uploaded

Make sure that you’ve reset your board by clicking the EN button on the ESP32 board after a new firmware (sketch) is uploaded. And also make sure that the serial port baud rate in Arduino IDE serial monitor matches the serial.begin() baud rate in your code.

不然，Arduino IDE Serial Monitor Blank or Printing Garbage

看见Arduino IDE Serial Monitor 输出后，在手机中和ESP32蓝牙配对

然后，使用“Serial Bluetooth Terminal“和ESP32通讯

```c
/*
* LAB Name: Android SmartPhone -> ESP32 Bluetooth (Slave)
* Author: Khaled Magdy
* DeepBlueMbedded 2023
* For More Info Visit: www.DeepBlueMbedded.com
*/
#include "BluetoothSerial.h"
 
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif
 
// LED GPIO Pin Definition
#define LED_GPIO 18
 
// Bluetooth Serial Object (Handle)
BluetoothSerial SerialBT;
 
// ESP32 Bluetooth (Slave) Device Information
const char *pin = "1234"; // Change this to more secure PIN.
String device_name = "ESP32-BT-Slave";
 
// Bluetooth Received Byte & Message Buffer Array
String RxBuffer = "";
char RxByte;
 
void setup() {
  pinMode(LED_GPIO, OUTPUT);
  Serial.begin(115200);
  SerialBT.begin(device_name); //Bluetooth device name
  Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());
  SerialBT.setPin(pin);
  Serial.println("Using PIN");
}
 
void loop() {
  // Read The Received Bytes & Add Them To Message (RxBuffer) Array
  if (SerialBT.available()){
    RxByte = SerialBT.read();
    if (RxByte != '\n'){
      RxBuffer += String(RxByte);
    }
    else{
      RxBuffer = "";
    }
    Serial.write(RxByte);  
  }
  // Check The Received Message & Update Output LED State
  if (RxBuffer =="led_on"){
    digitalWrite(LED_GPIO, HIGH);
  }
  else if (RxBuffer =="led_off"){
    digitalWrite(LED_GPIO, LOW);
  }
  delay(25);
}
```

## ESP32 Bluetooth With Android Smartphone (TX/RX)

In this example, we’ll exchange data between Android Smartphone serial Bluetooth Terminal and ESP32 Bluetooth Classic. The Smartphone will send led_on and led_off commands to the ESP32. And the ESP32 will receive the commands, control the LED accordingly, read the ADC channel of the potentiometer, and send the RAW ADC reading to the Smartphone over Bluetooth communication.


