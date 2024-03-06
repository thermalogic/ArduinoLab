#include <SPI.h>
#include <PCD8544.h>
#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
// Software SPI (slower updates, more flexible pin options):
// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
static PCD8544 lcd = PCD8544(7, 6, 5, 3, 4);

const int kPin_Temp = A0;

void setup()
{
  lcd.begin(84, 48);
  dht.begin();
  Serial.begin(9600);

  lcd.setCursor(10,0);
  lcd.print("Temperature: ");
  lcd.setCursor(10,2);
  lcd.print("Humidity:");
  
}

void loop()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  
  if (isnan(h) || isnan(t) || isnan(f)) {
    //failed to read readings from sensor
    return;
  }
  
  lcd.setCursor(21,1);
  lcd.print(t);
  lcd.print(" C");
  Serial.print("Temp: "); Serial.println(t);
  
  lcd.setCursor(21,3);
  lcd.print(h);
  lcd.print(" %");
  Serial.print("Humid: "); Serial.println(h);

  delay(100);
}
