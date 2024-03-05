/***********************************************************
File name: AdeeptLCD12864RSPI.h
Description: Demo LCD12864 spi
Website: www.adeept.com
E-mail: support@adeept.com
Author: Tom
Date: 2017/01/04 
***********************************************************/
#include <Arduino.h> 
#ifndef ADEEPT_LCD12864RSPI_h
#define ADEEPT_LCD12864RSPI_h
#include <avr/pgmspace.h>
#include <inttypes.h>


class LCD12864RSPI {
typedef unsigned char uchar;


public:

LCD12864RSPI();

void Initialise(void);
void delayns(void);

void WriteByte(int dat);
void WriteCommand(int CMD);
void WriteData(int CMD);


void CLEAR(void);
void DisplayString(int X,int Y,uchar *ptr,int dat);
void DisplaySig(int M,int N,int sig);
void DrawFullScreen(uchar *p);

int delaytime;
int DEFAULTTIME;


static const int latchPin = 8; 
static const int clockPin = 3;  
static const int dataPin = 9;  

};
extern LCD12864RSPI LCDA;    
#endif
