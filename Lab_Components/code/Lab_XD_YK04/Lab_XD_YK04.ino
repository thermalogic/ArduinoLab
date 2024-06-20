/*

pin 9 -> D0 - A
pin 10 ->D1 - B
pin 11 -> D2 - C
pin 12 ->D3 - D 
*/

void setup() {
  Serial.begin(9600);                           // setting the  baud rate
  Serial.println("RF receiver button decode");  // printing
}

void loop() {
  /*here in this code I used if statement to setup my loops codes, yo can  also use while loop statements to control the output in the serial monitor*/
  if (digitalRead(9) == HIGH) {  // Button a pressed
    Serial.println("you are pushing on the A");
    // if the Key is pushed this above text will be displayed
  }
  if (digitalRead(10) == HIGH) {  // Button B pressed
    Serial.println("you are pushing on B");
  }
  if (digitalRead(11) == HIGH) {  // Button C pressed
    Serial.println("you are pushing on C");
  }
  if (digitalRead(12) == HIGH) {  // Button D pressed
    Serial.println("you are pushing on D");
  }
}