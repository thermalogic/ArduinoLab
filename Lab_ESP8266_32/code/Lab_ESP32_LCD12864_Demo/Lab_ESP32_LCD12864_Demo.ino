/***********************************************************
File name:   AdeeptLCD12864SPI.ino
Website: www.adeept.com
E-mail: support@adeept.com
Author: Tom
Date: 2017/01/04
***********************************************************/
#include "AdeeptLCD12864RSPI.h"
#define AR_SIZE( a ) sizeof( a ) / sizeof( a[0] )

unsigned char show0[]="LCD 12864";         //Test the code
unsigned char show1[]="SPI interface";
unsigned char show2[]=" www.adeept.com";
unsigned char show3[]=" January 1,2017";
unsigned char logo0[]={
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xFF,
      0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0xFF,
      0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,
      0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x03,0xFE,0x00,
      0x7F,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x0F,0xF0,0x00,
      0x0F,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x1F,0x80,0x00,
      0x01,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x3E,0x00,0x00,
      0x00,0x7C,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0xF8,0x00,0x00,
      0x00,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x01,0xF0,0x00,0x00,
      0x00,0x0F,0x80,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x03,0xE0,0x00,0x00,
      0x00,0x07,0xC0,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x07,0xC0,0x00,0x00,
      0x00,0x01,0xE0,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x07,0x80,0x00,0x00,
      0x00,0x00,0xE0,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x0F,0x00,0x00,0x00,
      0x00,0x00,0xF0,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x1E,0x00,0x00,0x00,
      0x00,0x00,0x78,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x3C,0x00,0x00,0x00,
      0x00,0x00,0x3C,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x38,0x00,0x40,0x00,
      0x00,0x80,0x1C,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x78,0x03,0xF8,0x00,
      0x07,0xF0,0x1E,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x70,0x07,0xFE,0x00,
      0x0F,0xFC,0x0E,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0xF0,0x1F,0xBF,0x00,
      0x3F,0x7E,0x0F,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0xE0,0x3E,0x0F,0x80,
      0x7C,0x1F,0x07,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0xE0,0x7C,0x07,0xC0,
      0xF8,0x0F,0x87,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x01,0xE0,0xF8,0x01,0xE1,
      0xF0,0x03,0xC3,0x80,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x01,0xC0,0xF0,0x01,0xE1,
      0xE0,0x03,0xC3,0x80,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x01,0xC0,0xE0,0x00,0xE1,
      0xC0,0x01,0xC3,0x80,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x01,0xC0,0x00,0x00,0x00,
      0x00,0x00,0x03,0x80,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x03,0x80,0x00,0x00,0x00,
      0x00,0x00,0x01,0xC0,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x03,0x80,0x00,0x00,0x00,
      0x00,0x00,0x01,0xC0,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x03,0x80,0x00,0x00,0x00,
      0x00,0x00,0x01,0xC0,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x03,0x80,0x00,0x00,0x00,
      0x00,0x00,0x01,0xC0,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x03,0x80,0x00,0x00,0x00,
      0x00,0x00,0x01,0xC0,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x03,0x80,0x00,0x00,0x00,
      0x00,0x00,0x01,0xC0,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x03,0x80,0x00,0x00,0x00,
      0x00,0x00,0x01,0xC0,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x03,0x80,0x00,0x00,0x00,
      0x00,0x00,0x01,0xC0,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x03,0x80,0x00,0x00,0x00,
      0x00,0x00,0x01,0xC0,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x03,0x80,0x00,0x00,0x00,
      0x00,0x00,0x01,0xC0,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x01,0xC0,0x00,0x00,0x00,
      0x00,0x00,0x01,0x80,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x01,0xC0,0x00,0x00,0x00,
      0x00,0x00,0x03,0x80,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x01,0xC0,0x00,0x00,0x00,
      0x00,0x00,0x03,0x80,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x01,0xE0,0x00,0x00,0x00,
      0x00,0x00,0x03,0x80,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0xE0,0x00,0x00,0x00,
      0x00,0x00,0x07,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0xE0,0x00,0x00,0x00,
      0x00,0x00,0x07,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0xF0,0x00,0x0C,0x00,
      0x0C,0x00,0x0F,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x70,0x00,0x1E,0x00,
      0x1E,0x00,0x0E,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x78,0x00,0x1F,0x00,
      0x3E,0x00,0x1E,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x38,0x00,0x07,0x80,
      0xF8,0x00,0x1C,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x3C,0x00,0x03,0xE1,
      0xF0,0x00,0x3C,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x1E,0x00,0x01,0xFF,
      0xE0,0x00,0x78,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x0F,0x00,0x00,0xFF,
      0x80,0x00,0xF0,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x07,0x00,0x00,0x3F,
      0x00,0x00,0xF0,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x07,0x80,0x00,0x00,
      0x00,0x01,0xE0,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x03,0xE0,0x00,0x00,
      0x00,0x07,0xC0,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x01,0xF0,0x00,0x00,
      0x00,0x0F,0x80,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0xF8,0x00,0x00,
      0x00,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x3E,0x00,0x00,
      0x00,0x7E,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x1F,0x80,0x00,
      0x01,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x0F,0xE0,0x00,
      0x07,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x03,0xFE,0x00,
      0x3F,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,
      0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0xFF,
      0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xFF,
      0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

void setup()
{
LCDA.Initialise(); // The screen is initialized
delay(100);
}

void loop()
{
LCDA.CLEAR();//Clear screen
delay(100);
LCDA.DisplayString(0,2,show0,AR_SIZE(show0));//The first line of the third grid starts, showing
delay(100);
LCDA.DisplayString(1,1,show1,AR_SIZE(show1));//The first line of the second line starts, display
delay(100);
LCDA.DisplayString(2,0,show2,AR_SIZE(show2));//The third line of the first grid, display text
delay(100);
LCDA.DisplayString(3,0,show3,AR_SIZE(show3));//The third line of the first grid, display text
delay(5000);
LCDA.CLEAR();//Clear screen
delay(100);
LCDA.DrawFullScreen(logo0);
delay(5000);
}