/*
LCD1602A + DHT11
   based on
      1. DFRobot DHT11
      2. Arduino Examples:LiquidCrystal LCD1602A

*/

#include <DFRobot_DHT11.h>
DFRobot_DHT11 DHT;
#define DHT11_PIN 10

// include the library code:
#include <LiquidCrystal.h>
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
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
  DHT.read(DHT11_PIN);
  Serial.print("temp:");
  Serial.print(DHT.temperature);
  Serial.print("  humi:");
  Serial.println(DHT.humidity);
  lcd.clear();
  lcd.setCursor(0,0); 
  lcd.print("Temperature: ");
  lcd.print(DHT.temperature);
  lcd.setCursor(3,1); 
  lcd.print("Humidity: ");
  lcd.print(DHT.humidity);
  delay(1000);
}
