/*
  Blink
    Turns the RED_LED and GREEN_LED on for one second, then off for one second, repeatedly.
*/

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pins RED_LED and GREEN_LED as an output.
  pinMode(RED_LED, OUTPUT);
  //pinMode(GREEN_LED, OUTPUT);
  pinMode(P4_7, OUTPUT);
 
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(RED_LED, HIGH);  // turn the LED on (HIGH is the voltage level)
  digitalWrite(GREEN_LED, HIGH);  
  delay(1000);                      // wait for a second
  digitalWrite(RED_LED, LOW);   // turn the LED off by making the voltage LOW
  digitalWrite(GREEN_LED, LOW);  
  delay(1000);                      // wait for a second
}
