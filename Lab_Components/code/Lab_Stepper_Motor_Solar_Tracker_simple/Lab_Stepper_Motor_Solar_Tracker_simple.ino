/*
  Stepper Motor and  Solar tracing
int in1Pin = 8;
int in2Pin = 9;
int in3Pin = 10;
int in4Pin = 11;
*/

const int Left_PhotoResistor = A0;
const int Right_PhotoResistor = A1;

//variable to hold sensor value
int Left_sensorValue;
int Right_sensorValue;
int diff_sensorValue;

int turn_left_on = 0;
int turn_right_on = 0;

int turn_step_angle = 5;

void clockwise(int num) {
  for (int count = 0; count < num; count++) {
    for (int i = 8; i < 12; i++) {
      digitalWrite(i, HIGH);
      delay(3);
      digitalWrite(i, LOW);
    }
  }
}

void anticlockwise(int num) {
  for (int count = 0; count < num; count++) {
    for (int i = 11; i > 7; i--) {
      digitalWrite(i, HIGH);
      delay(3);
      digitalWrite(i, LOW);
    }
  }
}

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  for (int i = 8; i < 12; i++) {
    pinMode(i, OUTPUT);
  }
  Left_sensorValue = analogRead(Left_PhotoResistor);
  Right_sensorValue = analogRead(Right_PhotoResistor);

  Serial.print("Left sensorValue: ");
  Serial.println(Left_sensorValue);
  Serial.print("Right sensorValue: ");
  Serial.println(Right_sensorValue);
  diff_sensorValue = Left_sensorValue - Right_sensorValue;
  Serial.print("diff sensorValue: ");
  Serial.println(diff_sensorValue);
  delay(2000);
}

void loop() {
    if (Left_sensorValue - 30 > Right_sensorValue) {
      anticlockwise(turn_step_angle);  //turn Left
      Serial.println("Turning Left: ");
      turn_left_on = 1;
      turn_right_on = 0;
    };
      if (Right_sensorValue - 30 > Left_sensorValue) {
        clockwise(turn_step_angle);
        Serial.println("Turning Right: ");
        turn_left_on = 0;
        turn_right_on = 1;
      };
    Left_sensorValue = analogRead(Left_PhotoResistor);
    Right_sensorValue = analogRead(Right_PhotoResistor);
    Serial.print("Left sensorValue: ");
    Serial.println(Left_sensorValue);
    Serial.print("Right sensorValue: ");
    Serial.println(Right_sensorValue);
    diff_sensorValue = Left_sensorValue - Right_sensorValue;
    Serial.print("diff sensorValue: ");
    Serial.println(diff_sensorValue);
    delay(500);
};