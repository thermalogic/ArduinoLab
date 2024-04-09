#include <LiquidCrystal_I2C.h>

#include "component_ir.h"
#include "stepper_motor.h"

LiquidCrystal_I2C lcd(0x27, 16, 2); 

void setup() {

  Serial.begin(115200);
  // put your setup code here, to run once:
  lcd.init();          
  lcd.backlight();     
  lcd.setCursor(0, 0); 
  lcd.print("ESP32-C3 Demo");
  lcd.setCursor(0, 1); 
  lcd.print("       2024");


  setup_ir();

}

void loop() {
  // put your main code here, to run repeatedly:
  loop_ir();

  lcd.setCursor(0, 1);
  lcd.print(cur_cmd);
  
}
