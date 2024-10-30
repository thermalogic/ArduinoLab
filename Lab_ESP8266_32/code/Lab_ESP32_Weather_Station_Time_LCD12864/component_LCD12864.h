#ifndef LCD12864_H
#define LCD12864_H

#include "AdeeptLCD12864RSPI.h"
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

}



#endif /* LCD12864_H */