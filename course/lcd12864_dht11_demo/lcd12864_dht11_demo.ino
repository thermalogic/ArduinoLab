/***********************************************************
DHT11 Sensor with   LCD 12864 
  DFRobot_DHT11.h
  AdeeptLCD12864RSPI.h
***********************************************************/

#include <DFRobot_DHT11.h>
DFRobot_DHT11 DHT;
#define DHT11_PIN 7

#include "AdeeptLCD12864RSPI.h"
#define AR_SIZE(a) sizeof(a) / sizeof(a[0])

unsigned char show0[] = "DHT11 sensor";  //Test the code
unsigned char show1[] = "Humi:       %";
unsigned char show2[] = "Temp:       C";
unsigned char show3[] = " Cheng Maohua";

void setup() {

  Serial.begin(9600);
  LCDA.Initialise();  // The screen is initialized
  delay(100);
  // LCDA.CLEAR();//Clear screen
  delay(100);
  LCDA.DisplayString(0, 1, show0, AR_SIZE(show0));  //Display: DHT11 sensor
  delay(100);
  LCDA.DisplayString(1, 1, show1, AR_SIZE(show1));  //Display: Humi:     %
  delay(100);
  LCDA.DisplayString(2, 1, show2, AR_SIZE(show2));  //Display: Temp:     C
  delay(100);
  LCDA.DisplayString(3, 1, show3, AR_SIZE(show3));  //Display: www.adeept.com
}

void loop() {
  char strhumidity[5];
  char strTemperature[5];

  DHT.read(DHT11_PIN);
  Serial.print("temp:");
  Serial.print(DHT.temperature);
  Serial.print("  humi:");
  Serial.println(DHT.humidity);
  dtostrf(DHT.temperature, 5, 2, strTemperature);                //Converts a floating-point number to a string
  LCDA.DisplayString(1, 4, (unsigned char *)strTemperature, 6);  //Display humidity data
  dtostrf(DHT.humidity, 5, 2, strhumidity);                      //Converts a floating-point number to a string
  LCDA.DisplayString(2, 4, (unsigned char *)strhumidity, 6);     //Display humidity data
  delay(1000);
}