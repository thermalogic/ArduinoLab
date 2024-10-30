/***********************************************************
  AdeeptLCD12864RSPI.h
***********************************************************/
#ifndef LCD12864_H
#define LCD12864_H

#include "AdeeptLCD12864RSPI.h"
#include "component_dht11.h"
#define AR_SIZE(a) sizeof(a) / sizeof(a[0])

unsigned char show1[] = "Temp:   C";
unsigned char show2[] = "Humi:   %";
unsigned char show3[] = " Web: ";

void setup_lcd12864() {
  LCDA.Initialise();  // The screen is initialized
  delay(100);
  // LCDA.CLEAR();//Clear screen
  LCDA.DisplayString(1, 1, show1, AR_SIZE(show1));
  delay(100);
  LCDA.DisplayString(2, 1, show2, AR_SIZE(show2));
  delay(100);
  LCDA.DisplayString(3, 0, show3, AR_SIZE(show3));
}

void loop_lcd12864() {
  char strTemperature[4];
  char strhumidity[4];
  dtostrf(Temperature, 4, 2, strTemperature);                    // Converts a floating-point number to a string
  LCDA.DisplayString(1,4, (unsigned char *)strTemperature,2);  // Display humidity data
  dtostrf(Humidity, 4, 2, strhumidity);                          // Converts a floating-point number to a string
  LCDA.DisplayString(2,4, (unsigned char *)strhumidity, 2);     // Display humidity data
}

#endif /* LCD12864_H */