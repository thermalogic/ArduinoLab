
/*
  2WD wheels+ IRmote+ Led + Ultrasonic + speed
*/

#include <Arduino.h>
#include "PinDefinitionsAndMore.h" // Define macros for input and output pin etc.
#include <IRremote.hpp>

#define LeftForward 3  // Motor Red +   LS298N IN4 -> Arduino Pin3
#define LeftBack 4     // Motor  black - LS298N IN3 -> Arduino Pin4
#define RightForward 8 // Motor balck -  LS298N IN1-> Arduino Pin8
#define RightBack 7    // Motor red +   LS298N IN2 -> Arduino Pin7

#define leftPWM 5
#define rightPWM 6

#define MOTOR_GO 0
#define MOTOR_BACK 1
#define MOTOR_STOP 2
#define MOTOR_LEFT 3
#define MOTOR_RIGHT 4

int speed_level1 = 100; // 转向时用，转速差，转向
int speed_level2 = 200; // 太低驱动不了，调试后200，比较合适
int speed_level3 = 250;

int motor_state = MOTOR_STOP;

#define LED_Left 9
#define LED_Right 10

#define DECODE_NEC // Includes Apple and Onkyo
#define IR_RECEIVE_PIN 11

int trigPin = 12; // Trigger
int echoPin = 13; // Echo
long duration, cm;

void init_car()
{
  // 默认停止状态
  analogWrite(leftPWM, 0);
  analogWrite(rightPWM, 0);
  // 默认全是低电平 停止状态
  digitalWrite(LeftForward, LOW);
  digitalWrite(LeftBack, LOW);
  digitalWrite(RightForward, LOW);
  digitalWrite(RightBack, LOW);
  motor_state = MOTOR_STOP;
}

void go()
{
  // 左轮前进
  analogWrite(leftPWM, speed_level2);
  digitalWrite(LeftForward, HIGH);
  digitalWrite(LeftBack, LOW);
  // 右轮前进
  analogWrite(rightPWM, speed_level2);
  digitalWrite(RightForward, HIGH);
  digitalWrite(RightBack, LOW);
  motor_state = MOTOR_GO;
}

void back()
{
  analogWrite(leftPWM, speed_level2);
  // 左轮后退
  digitalWrite(LeftForward, LOW);
  digitalWrite(LeftBack, HIGH);
  // 右轮后退
  analogWrite(rightPWM, speed_level2);
  digitalWrite(RightForward, LOW);
  digitalWrite(RightBack, HIGH);
  motor_state = MOTOR_BACK;
}

/* 左转 */
void turn_left()
{
  // 左轮低速
  analogWrite(leftPWM, speed_level1);
  digitalWrite(LeftForward, HIGH);
  digitalWrite(LeftBack, LOW);
  // 右轮前进
  analogWrite(rightPWM, speed_level2);
  digitalWrite(RightForward, HIGH);
  digitalWrite(RightBack, LOW);
  motor_state = MOTOR_LEFT;
}

/* 右转 */
void turn_right()
{
  // 左轮前进
  analogWrite(leftPWM, speed_level2);
  digitalWrite(LeftForward, HIGH);
  digitalWrite(LeftBack, LOW);
  // 右轮低速
  analogWrite(rightPWM, speed_level1);
  digitalWrite(RightForward, HIGH);
  digitalWrite(RightBack, LOW);
  motor_state = MOTOR_RIGHT;
}

void stop_car()
{
  init_car();
}

class Flasher
{
  int ledPin;   // the number of the LED pin
  long OnTime;  // milliseconds of on-time
  long OffTime; // milliseconds of off-time
  // These maintain the current state
  int led_state; // led_state used to set the LED
public:
  unsigned long previousMillis; // will store last time LED was updated

public:
  Flasher(int pin, long on_time, long off_time)
  {
    ledPin = pin;
    pinMode(ledPin, OUTPUT);
    OnTime = on_time;
    OffTime = off_time;
    led_state = LOW;
    digitalWrite(ledPin, led_state);
  };

  void on()
  {
    led_state = HIGH;
    digitalWrite(ledPin, led_state);
  }

  void off()
  {
    led_state = LOW;
    digitalWrite(ledPin, led_state);
  }

  void update()
  {
    unsigned long currentMillis = millis();
    if ((led_state == HIGH) && (currentMillis - previousMillis >= OnTime))
    {
      led_state = LOW;                 // Turn it off
      previousMillis = currentMillis;  // Remember the time
      digitalWrite(ledPin, led_state); // Update the actual LED
    }
    else if ((led_state == LOW) && (currentMillis - previousMillis >= OffTime))
    {
      led_state = HIGH;                // turn it on
      previousMillis = currentMillis;  // Remember the time
      digitalWrite(ledPin, led_state); // Update the actual LED
    };
  };
};

Flasher led_left(LED_Left, 500, 500);
Flasher led_right(LED_Right, 500, 500);

void setup()
{
  // 1 motor
  pinMode(LeftForward, OUTPUT);
  pinMode(LeftBack, OUTPUT);
  pinMode(RightForward, OUTPUT);
  pinMode(RightBack, OUTPUT);

  // speedcontrol
  pinMode(leftPWM, OUTPUT);
  pinMode(rightPWM, OUTPUT);

  init_car();

  // 2 irremote
  Serial.begin(9600);
  // Just to know which program is running on my Arduino
  Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));

  // Start the receiver and if not 3. parameter specified, take LED_BUILTIN pin from the internal boards definition as default feedback LED
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

  Serial.print(F("Ready to receive IR signals of protocols: "));
  printActiveIRProtocols(&Serial);
  Serial.println(F("at pin " STR(IR_RECEIVE_PIN)));

  //  ultrasonic - Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop()
{

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
  cm = (duration / 2) / 29.1; // Divide by 29.1 or multiply by 0.0343
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  if (cm < 25.0)
  {
    if (motor_state == MOTOR_GO || motor_state == MOTOR_LEFT || motor_state == MOTOR_RIGHT)
      stop_car();
    led_left.off();
    led_right.off();
  }

  if (motor_state == MOTOR_BACK)
  {
    led_left.update();
    led_right.update();
  }

  if (IrReceiver.decode())
  {
    // Print a short summary of received data
    IrReceiver.printIRResultShort(&Serial);
    IrReceiver.printIRSendUsage(&Serial);
    if (IrReceiver.decodedIRData.protocol == UNKNOWN)
    {
      Serial.println(F("Received noise or an unknown (or not yet enabled) protocol"));
      // We have an unknown protocol here, print more info
      IrReceiver.printIRResultRawFormatted(&Serial, true);
    }
    Serial.println();

    //!!!Important!!! Enable receiving of the next value,
    IrReceiver.resume(); // Enable receiving of the next value

    // Finally, check the received data and perform actions according to the received command
    if (IrReceiver.decodedIRData.command == 0x11 || IrReceiver.decodedIRData.command == 0x18)
    {
      // forward - 2
      if (motor_state != MOTOR_GO)
      {
        led_left.on();
        led_right.on();
        go();
      }
    }
    else if (IrReceiver.decodedIRData.command == 0x14 || IrReceiver.decodedIRData.command == 0x8)
    {
      // Left - 4
      if (motor_state != MOTOR_LEFT)
      {
        led_left.on();
        led_right.off();
        turn_left();
      }
    }
    else if (IrReceiver.decodedIRData.command == 0x16 || IrReceiver.decodedIRData.command == 0x5A)
    {
      // right - 6
      if (motor_state != MOTOR_RIGHT)
      {
        led_left.off();
        led_right.on();
        turn_right();
      }
    }
    else if (IrReceiver.decodedIRData.command == 0x19 || IrReceiver.decodedIRData.command == 0x52)
    {
      // back -5
      if (motor_state != MOTOR_BACK)
      {
        back();
        led_left.off();
        led_right.off();
        led_left.previousMillis = 0;
        led_right.previousMillis = 0;
        led_left.update();
        led_right.update();
      }
    }
    else if (IrReceiver.decodedIRData.command == 0x15 || IrReceiver.decodedIRData.command == 0x1C)
    {
      // stop -8
      if (motor_state != MOTOR_STOP)
      {
        led_left.off();
        led_right.off();
        stop_car();
      };
    }
  }
}
