#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); 

void setup() {
  // put your setup code here, to run once:
  lcd.init();          
  lcd.backlight();     
  lcd.setCursor(0, 0); 
  lcd.print("ESP32-C3 Demo");
  lcd.setCursor(0, 1); 
  lcd.print("       2024");

}

void loop() {
  // put your main code here, to run repeatedly:

}
