/*
 * Interfacing Arduino with Nokia 5110 LCD and DHT11 sensor.
 * This is a free software with NO WARRANTY.
 */
 
#include <SPI.h>               // include SPI library
#include <Adafruit_GFX.h>      // include adafruit graphics library
#include <Adafruit_PCD8544.h>  // include adafruit PCD8544 (Nokia 5110) library
           // include DHT library code
#include <DFRobot_DHT11.h>
DFRobot_DHT11 DHT;
#define DHT11_PIN 10

// Nokia 5110 LCD module connections (CLK, DIN, D/C, CS, RST)
Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);
  
void setup()
{
  Serial.begin(9600);
  delay(1000);  // wait 1 second
  // initialize the display
  display.begin();
  // you can change the contrast around to adapt the display
  // for the best viewing!
  display.setContrast(65);
  display.clearDisplay();   // clear the screen and buffer
  display.drawFastHLine(0, 23, display.width(), BLACK);
  display.setTextSize(1);
  display.setTextColor(BLACK, WHITE);
  display.setCursor(6, 0);
  display.print("TEMPERATURE:");
  display.setCursor(56, 12);
  display.print("C");
 
  display.setCursor(15, 28);
  display.print("HUMIDITY:");
  display.setCursor(56,40);
  display.print("%");
  display.display();
}
 
// main loop
void loop()
{
  char strhumidity[5];
  char strTemperature[5];
  DHT.read(DHT11_PIN);
  Serial.print("temp:");
  Serial.print(DHT.temperature);
  Serial.print("  humi:");
  Serial.println(DHT.humidity);
 
  // print temperature
  dtostrf(DHT.temperature, 5, 2, strTemperature); 
  display.setCursor(24, 12);
  display.print(strTemperature);
 
  // print humidity
  dtostrf(DHT.humidity, 5, 2, strhumidity);     
  display.setCursor(24, 40);
  display.print(strhumidity);
 
 
 // now update the display
  display.display();
  delay(100);  // wait 1 second
 
}
// end of code.