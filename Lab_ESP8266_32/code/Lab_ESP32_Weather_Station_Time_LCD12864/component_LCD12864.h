/***********************************************************
  AdeeptLCD12864RSPI.h
***********************************************************/
#ifndef LCD12864_H
#define LCD12864_H

#include "AdeeptLCD12864RSPI.h"
#include "component_dht11.h"
#define AR_SIZE(a) sizeof(a) / sizeof(a[0])

unsigned char show1[] = " RoomTH: ";
unsigned char show2[] = " EnviTH: ";

void setup_lcd12864() {
  LCDA.Initialise();  // The screen is initialized
  delay(100);
  // LCDA.CLEAR();//Clear screen
  LCDA.DisplayString(1,0, show1, AR_SIZE(show1));
  delay(100);
  LCDA.DisplayString(2,0, show2, AR_SIZE(show2));
}

void loop_lcd12864() {
  char strTemperature[4];
  char strhumidity[4];
  dtostrf(Temperature, 4, 2, strTemperature);                    // Converts a floating-point number to a string
  LCDA.DisplayString(1,4, (unsigned char *)strTemperature,2);  // Display humidity data
  dtostrf(Humidity, 4, 2, strhumidity);                          // Converts a floating-point number to a string
  LCDA.DisplayString(1,6, (unsigned char *)strhumidity, 2);     // Display humidity data
}



#endif /* LCD12864_H */