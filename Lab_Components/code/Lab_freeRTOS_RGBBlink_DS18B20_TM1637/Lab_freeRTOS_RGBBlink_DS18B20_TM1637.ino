#include <Arduino_FreeRTOS.h>
#include <Arduino.h>
#include "rgbled.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <TM1637Display.h>

// define two tasks for Blink & AnalogRead
void TaskBlink(void *pvParameters);
void TaskTempRead(void *pvParameters);

// the setup function runs once when you press reset or power the board
void setup() {

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  // Now set up two tasks to run independently.
  xTaskCreate(
    TaskBlink, "link"  // A name just for humans
    ,
    128  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,
    NULL, 2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,
    NULL);

  xTaskCreate(
    TaskTempRead, "TempRead", 256  // Stack size
    ,
    NULL, 1  // Priority
    ,
    NULL);

  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}

void loop() {
  // Empty. Things are done in Tasks.
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void TaskBlink(void *pvParameters)  // This is a task.
{
  (void)pvParameters;
  rgbled my_rgbled(9, 8, 7, 'c');
  for (;;)  // A Task shall never return or exit.
  {
    my_rgbled.out(100, 0, 0);              // red
    vTaskDelay(500 / portTICK_PERIOD_MS);  // wait for one second
    my_rgbled.out(0, 100, 0);              // green
    vTaskDelay(500 / portTICK_PERIOD_MS);  // wait for one second
    my_rgbled.out(0, 0, 100);              // blue
    vTaskDelay(500 / portTICK_PERIOD_MS); 
    my_rgbled.out(0, 100, 100);              // 
    vTaskDelay(500 / portTICK_PERIOD_MS);  
    my_rgbled.out(100, 100, 100);            // white 
    vTaskDelay(500 / portTICK_PERIOD_MS);  
    my_rgbled.out(100, 100,0);              // 
    vTaskDelay(500 / portTICK_PERIOD_MS);     
  }
}

void TaskTempRead(void *pvParameters)  // This is a task.
{

  (void)pvParameters;

  int CLK = 2;
  int DIO = 3;
  // Data wire is plugged into port 12 on the Arduino
  int ONE_WIRE_BUS = 12;

  // Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
  OneWire oneWire(ONE_WIRE_BUS);
  // Pass our oneWire reference to Dallas Temperature.
  DallasTemperature sensors(&oneWire);
  TM1637Display display(CLK, DIO);
  sensors.begin();

  for (;;) {

    // call sensors.requestTemperatures() to issue a global temperature
    // request to all devices on the bus
    sensors.requestTemperatures();  // Send the command to get temperatures
    // After we got the temperatures, we can print them here.
    // We use the function ByIndex, and as an example get the temperature from the first sensor only.
    float tempC = sensors.getTempCByIndex(0);
    // Check if reading was successful
    if (tempC != DEVICE_DISCONNECTED_C) {
      Serial.print("Temperature for the device 1 (index 0) is: ");
      Serial.println(tempC);
    } else {
     Serial.println("Error: Could not read temperature data");
    }

    display.setBrightness(0x0f);
    display.showNumberDec(tempC, false);
  }
  vTaskDelay(50);  //50*15ms，50  ticks delay， each tick  delay=15ms
}
