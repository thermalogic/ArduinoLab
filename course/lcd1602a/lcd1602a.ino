/*
LCD1602A
 

*/


// include the library code:
#include <LiquidCrystal.h>
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 4, d5 = 5, d6 =6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup(){
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("Welcome to ");
  lcd.setCursor(0,1);    
  lcd.print("  Arduino World!");
  delay(2000);
}

void loop(){
    lcd.print("Welcome to ");
  lcd.setCursor(0,1);    
  lcd.print("  Arduino World!");
}
