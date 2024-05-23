/*
 * LCD1602 I2C 
   DHT11
 */
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include <DFRobot_DHT11.h>
DFRobot_DHT11 DHT;
#define DHT11_PIN 7

 
LiquidCrystal_I2C lcd(0x27,16,2);  //配置LCD地址及行列
 
void setup(){
  lcd.init(); //初始化LCD
  lcd.backlight(); //打开背光
  lcd.setCursor(0,0);//设置显示位置
  lcd.print("Welcome To");//显示字符数据
  lcd.setCursor(0,1);//设置显示位置
  lcd.print(" Arduino World");//显示字符数据
  delay(1000);
}
 
void loop()
{
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