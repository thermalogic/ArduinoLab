int leftCounter = 0, rightCounter = 0;
unsigned long time = 0, old_time = 0;  // 时间标记
unsigned long time1 = 0;               // 时间标记
float lv, rv;                          //左、右轮速度
#define STOP 0
#define FORWARD 1
#define BACKWARD 2
#define TURNLEFT 3
#define TURNRIGHT 4
#define CHANGESPEED 5
int leftMotor1 = 16;
int leftMotor2 = 17;
int rightMotor1 = 18;
int rightMotor2 = 19;
bool speedLevel = 0;
int leftPWM = 5;
int rightPWM = 6;
void setup() {

  // put your setup code here, to run once:
  Serial.begin(9600);
  attachInterrupt(0, RightCount_CallBack, FALLING);
  attachInterrupt(1, LeftCount_CallBack, FALLING);
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);
  pinMode(leftPWM, OUTPUT);
  pinMode(rightPWM, OUTPUT);
}
void loop() {

  // put your main code here, to run repeatedly:
  SpeedDetection();
  if (Serial.available() > 0) {

    char cmd = Serial.read();
    Serial.print(cmd);
    motorRun(cmd);
    if (speedLevel)  //根据不通的档位输出不同速度
    {

      analogWrite(leftPWM, 120);
      analogWrite(rightPWM, 120);
    } else {

      analogWrite(leftPWM, 250);
      analogWrite(rightPWM, 250);
    }
  }
}
/* * *速度计算 */
bool SpeedDetection() {

  time = millis();                   //以毫秒为单位，计算当前时间
  if (abs(time - old_time) >= 1000)  // 如果计时时间已达1秒
  {

    detachInterrupt(0);  // 关闭外部中断0
    detachInterrupt(1);  // 关闭外部中断1
    //把每一秒钟编码器码盘计得的脉冲数，换算为当前转速值
    //转速单位是每分钟多少转，即r/min。这个编码器码盘为20个空洞。
    Serial.print("left:");
    lv = (float)leftCounter * 60 / 20;   //小车车轮电机转速
    rv = (float)rightCounter * 60 / 20;  //小车车轮电机转速
    Serial.print("left:");
    Serial.print(lv);  //向上位计算机上传左车轮电机当前转速的高、低字节
    Serial.print(" right:");
    Serial.println(rv);  //向上位计算机上传左车轮电机当前转速的高、低字节
    //恢复到编码器测速的初始状态
    leftCounter = 0;  //把脉冲计数值清零，以便计算下一秒的脉冲计数
    rightCounter = 0;
    old_time = millis();                               // 记录每秒测速时的时间节点
    attachInterrupt(0, RightCount_CallBack, FALLING);  // 重新开放外部中断0
    attachInterrupt(1, LeftCount_CallBack, FALLING);   // 重新开放外部中断0
    return 1;
  } else
    return 0;
}
/* * *右轮编码器中断服务函数 */
void RightCount_CallBack() {

  rightCounter++;
}
/* * *左轮编码器中断服务函数 */
void LeftCount_CallBack() {

  leftCounter++;
}
/* * *小车运动控制函数 */
void motorRun(int cmd) {

  switch (cmd) {

    case FORWARD:
      Serial.println("FORWARD");  //输出状态
      digitalWrite(leftMotor1, HIGH);
      digitalWrite(leftMotor2, LOW);
      digitalWrite(rightMotor1, HIGH);
      digitalWrite(rightMotor2, LOW);
      break;
    case BACKWARD:
      Serial.println("BACKWARD");  //输出状态
      digitalWrite(leftMotor1, LOW);
      digitalWrite(leftMotor2, HIGH);
      digitalWrite(rightMotor1, LOW);
      digitalWrite(rightMotor2, HIGH);
      break;
    case TURNLEFT:
      Serial.println("TURN LEFT");  //输出状态
      digitalWrite(leftMotor1, HIGH);
      digitalWrite(leftMotor2, LOW);
      digitalWrite(rightMotor1, LOW);
      digitalWrite(rightMotor2, HIGH);
      break;
    case TURNRIGHT:
      Serial.println("TURN RIGHT");  //输出状态
      digitalWrite(leftMotor1, LOW);
      digitalWrite(leftMotor2, HIGH);
      digitalWrite(rightMotor1, HIGH);
      digitalWrite(rightMotor2, LOW);
      break;
    case CHANGESPEED:
      Serial.println("CHANGE SPEED");  //输出状态
      if (speedLevel)                  //接收到换挡命令的时候切换档位
        speedLevel = 0;
      else
        speedLevel = 1;
      break;
    default:
      Serial.println("STOP");  //输出状态
      digitalWrite(leftMotor1, LOW);
      digitalWrite(leftMotor2, LOW);
      digitalWrite(rightMotor1, LOW);
      digitalWrite(rightMotor2, LOW);
  }
}