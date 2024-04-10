/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-dc-motor-l298n-motor-driver-control-speed-direction/
*********/

// Motor A
int motor1Pin1 = 1; 
int motor1Pin2 = 12; 
// Motor B
int motor2Pin1 = 10; //  BIN1 绿色
int motor2Pin2 = 3; // BIN2 黄色

// Setting PWM properties
const int freq = 30000;
const int pwmChannel_motor1 = 0;
const int pwmChannel_motor2 = 1;
const int resolution = 8;
int dutyCycle = 200;


// motor action code
const int DEV_GO = 1;
const int DEV_BACK = 2;
const int DEV_LEFT = 3;
const int DEV_RIGHT = 4;
const int DEV_STOP = 5;

// PWM - speed
const int left_speed = 255;
const int right_speed = 255;
const int turn_speed_diff = 120;

void car_forward()
{
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  
  ledcWrite(pwmChannel_motor1, left_speed);
  ledcWrite(pwmChannel_motor2, right_speed);     
 }

void car_back()
{

}

void car_stop()
{
}

void car_turn_left()
{
}

void car_turn_right()
{
}

void car_action(int car_cmd)
{
  switch (car_cmd)
  {
  case DEV_GO:
    car_forward();
    break;
  case DEV_LEFT:
    car_turn_left();
    break;
  case DEV_RIGHT:
    car_turn_right();
    break;
  case DEV_BACK:
    car_back();
    break;
  case DEV_STOP:
    car_stop();
    break;
  default:
    break;
  } // switch
};

void setup() {
  // sets the pins as outputs:
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);


     // configure LED PWM functionalitites
  ledcSetup(pwmChannel_motor1, freq, resolution);
  ledcSetup(pwmChannel_motor2, freq, resolution);
  ledcAttachPin(motor1Pin1, pwmChannel_motor1);
  ledcAttachPin(motor2Pin1, pwmChannel_motor2);

  Serial.begin(115200);
 // testing
  Serial.print("Testing DC Motor...");
}


void loop() {
  // Move the DC motor forward at maximum speed
  Serial.println("Moving Forward");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH); 
  delay(2000);

  // Stop the DC motor
  Serial.println("Motor stopped");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  delay(1000);

  // Move DC motor backwards at maximum speed
  Serial.println("Moving Backwards");
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW); 
  delay(2000);

  // Stop the DC motor
  Serial.println("Motor stopped");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  delay(1000);

  // Move DC motor forward with increasing speed
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  while (dutyCycle <= 255){
    ledcWrite(pwmChannel_motor1, dutyCycle);   
    Serial.print("Forward with duty cycle: ");
    Serial.println(dutyCycle);
    dutyCycle = dutyCycle + 5;
    delay(500);
  }
  dutyCycle = 200;
}