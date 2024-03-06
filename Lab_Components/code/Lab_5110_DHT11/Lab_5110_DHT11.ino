/*
 * Interfacing Arduino with Nokia 5110 LCD and DHT11 sensor.
 * This is a free software with NO WARRANTY.
 * https://simple-circuit.com/
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
  display.setContrast(50);
 
  display.clearDisplay();   // clear the screen and buffer
 
  display.drawFastHLine(0, 23, display.width(), BLACK);
 
  display.setTextSize(1);
  display.setTextColor(BLACK, WHITE);
  display.setCursor(6, 0);
  display.print("TEMPERATURE:");
  display.setCursor(15, 28);
  display.print("HUMIDITY:");
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
  dtostrf(DHT.temperature, 5, 2, strTemperature); 
  dtostrf(DHT.humidity, 5, 2, strhumidity);     
  // print temperature
  display.setCursor(24, 12);
  display.print(strTemperature);
  // print humidity
  display.setCursor(24, 40);
  display.print(strhumidity);
  // print degree symbol ( ° )
  display.drawRect(50, 12, 3, 3, BLACK);
  // now update the display
  display.display();
  delay(1000);  // wait 1 second
 
}
// end of code.