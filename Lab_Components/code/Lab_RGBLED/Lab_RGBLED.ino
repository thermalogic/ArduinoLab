#include "rgbled.h"

/*
 * rgbled 'objectname' (Pin red LED(int), Pin green LED(int), Pin blue LED (int), char 'c' or 'a' for common cathode oder common anode)
 * .out(char values for r,g,b --> 0...255)
 * .preset -->  1: pulsing red
 *              2: pulsing green
 *              3: pulsing blue
 *              4: rgb fading
 */

rgbled my_rgbled(10,11,12, 'c');

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  my_rgbled.out(100,0,0);  // red
  delay(2000);
  my_rgbled.out(0,100,0);  // green
  delay(2000);
  my_rgbled.out(0,0,100);  // blue
  delay(2000);
  my_rgbled.out(0,0,0);  // off
  my_rgbled.preset(1);
  delay(2000);
  my_rgbled.out(0,0,0);  // off
  my_rgbled.preset(2);
  delay(2000);
  my_rgbled.out(0,0,0);  // off
  my_rgbled.preset(3);
  delay(2000);
  my_rgbled.out(0,0,0);  // off
} 
