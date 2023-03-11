/*
  测速+调速
 Motor Black -  High -> Forward
 Motor Red +  High -> Back 

*/

#define LeftForward 4   // Motor Black -     LS298N IN1 -> Arduino Pin4
#define LeftBack 5      // Motor Red     +     LS298N IN2 -> Arduino Pin5
#define RightForward 6  // Motor Black -     LS298N IN3 -> Arduino Pin6
#define RightBack 7     // Motor Red     +     LS298N IN4 -> Arduino Pin7

// 测速 left int1 pin3,
//      right: int0 pin2
int leftCounter = 0, rightCounter = 0;
unsigned long time = 0, old_time = 0;  // 时间标记
unsigned long time1 = 0;               // 时间标记
float lv, rv;                          //左、右轮速度
// 调整速度
bool speedLevel = 0;
int leftPWM = 5;  //和现在的电机pin冲突，需要调整电机驱动的pins
int rightPWM = 6;

void setup() {
  // 测速
  Serial.begin(9600);
  attachInterrupt(0, RightCount_CallBack, FALLING);
  attachInterrupt(1, LeftCount_CallBack, FALLING);
  // 调整速度
  pinMode(leftPWM, OUTPUT);
  pinMode(rightPWM, OUTPUT);

  pinMode(LeftForward, OUTPUT);
  pinMode(LeftBack, OUTPUT);
  pinMode(RightForward, OUTPUT);
  pinMode(RightBack, OUTPUT);
  initCar();
  delay(2000);
}

void loop() {
  // 测速
  SpeedDetection();
  go();
  delay(2000);
  // back();
  // delay(2000);
  stopCar();
  delay(2000);
  turnLeft();
  delay(2000);
  stopCar();
  // turnRight();
  delay(2000);
  if (Serial.available() > 0) {
    char cmd = Serial.read();
    Serial.print(cmd);
    if (cmd == 0)
      stopCar();
  }
  // 调整速度
  if (speedLevel)  //根据不通的档位输出不同速度
  {

    analogWrite(leftPWM, 120);
    analogWrite(rightPWM, 120);
  } else {

    analogWrite(leftPWM, 250);
    analogWrite(rightPWM, 250);
  }
}


/*
 * *速度计算
 */
bool SpeedDetection() {
  time = millis();                   //以毫秒为单位，计算当前时间
  if (abs(time - old_time) >= 1000)  // 如果计时时间已达1秒
  {
    detachInterrupt(0);  // 关闭外部中断0
    detachInterrupt(1);  // 关闭外部中断1
    //把每一秒钟编码器码盘计得的脉冲数，换算为当前转速值
    //转速单位是每分钟多少转，即r/min。这个编码器码盘为20个空洞。
    lv = (float)leftCounter * 60 / 20;   //小车车轮电机转速
    rv = (float)rightCounter * 60 / 20;  //小车车轮电机转速
    Serial.print("left:");
    Serial.print(lv);  //向上位计算机上传左车轮电机当前转速的高、低字节
    Serial.print("     right:");
    Serial.println(rv);  //向上位计算机上传左车轮电机当前转速的高、低字节
    //恢复到编码器测速的初始状态
    leftCounter = 0;  //把脉冲计数值清零，以便计算下一秒的脉冲计数
    rightCounter = 0;
    old_time = millis();  // 记录每秒测速时的时间节点
    // 测速 left int1 pin3,
    //  right: int0 pin2
    attachInterrupt(0, RightCount_CallBack, FALLING);  // 重新开放外部中断0
    attachInterrupt(1, LeftCount_CallBack, FALLING);   // 重新开放外部中断0
    return 1;
  } else
    return 0;
}

/*
 * *左轮编码器中断服务函数
 */
void LeftCount_CallBack() {
  leftCounter++;
}

/*
 * *右轮编码器中断服务函数
 */
void RightCount_CallBack() {
  rightCounter++;
}

void initCar() {
  //默认全是低电平 停止状态
  digitalWrite(LeftForward, LOW);
  digitalWrite(LeftBack, LOW);
  digitalWrite(RightForward, LOW);
  digitalWrite(RightBack, LOW);
}

void go() {
  // 左轮前进
  digitalWrite(LeftForward, HIGH);
  digitalWrite(LeftBack, LOW);
  // 右轮前进
  digitalWrite(RightForward, HIGH);
  digitalWrite(RightBack, LOW);
}

void back() {
  //左轮后退
  digitalWrite(LeftForward, LOW);
  digitalWrite(LeftBack, HIGH);
  //右轮后退
  digitalWrite(RightForward, LOW);
  digitalWrite(RightBack, HIGH);
}

/* 左转 */
void turnLeft() {
  //左轮不动
  digitalWrite(LeftForward, LOW);
  digitalWrite(LeftBack, LOW);
  // 右轮前进
  digitalWrite(RightForward, HIGH);
  digitalWrite(RightBack, LOW);
}

/* 右转 */
void turnRight() {
  // 左轮前进
  digitalWrite(LeftForward, HIGH);
  digitalWrite(LeftBack, LOW);
  // 右轮不动
  digitalWrite(RightForward, LOW);
  digitalWrite(RightBack, LOW);
}

void stopCar() {
  initCar();
}