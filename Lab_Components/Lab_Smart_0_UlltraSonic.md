# Ultrasonic

## Ultrasonic

* HC-SR04

**测距失败**： 传感器坏了？？？

## 连接

![](./img/Ultrasonic/Ultrasonic_Arduino.jpg)

![Arduino-SR04](./img/Ultrasonic/Arduino-SR04.png)


 Module HR-SC04 (four pins)  attached to digital pins as follows:
 
  
 | HC-SR04 | Arduino |    
 |---------|---------|   
 |   Vcc   |   5V    |   
 |   Trig  |   12    | 
 |   Echo  |   13    | 
 |   Gnd   |   GND   |


## code 
```c
/*
 * created by Rui Santos, https://randomnerdtutorials.com
 * 
 * Complete Guide for Ultrasonic Sensor HC-SR04
 *
    Ultrasonic sensor Pins:
        VCC: +5VDC
        Trig : Trigger (INPUT) - Pin12
        Echo: Echo (OUTPUT) - Pin 13
        GND: GND
 */
 
int trigPin = 12;    // Trigger
int echoPin = 13;    // Echo
long duration, cm, inches;
 
void setup() {
  //Serial Port begin
  Serial.begin (9600);
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
 
void loop() {
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
  // Convert the time into a distance
  cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  inches = (duration/2) / 74;   // Divide by 74 or multiply by 0.0135
  
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  delay(250);
}
```
## 库

Erick Simões (github: @ErickSimoes

![](./img/Ultrasonic/Ultrasonic_lib.jpg)

