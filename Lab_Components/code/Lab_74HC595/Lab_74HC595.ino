#define LATCH_pin 11      // (11) ST_CP [RCK] on 74HC595
#define CLCOK_pin  9      // (9) SH_CP [SCK] on 74HC595
#define DATA_pin 12     // (12) DS [S1] on 74HC595

void clock_signal(void){
   digitalWrite(CLCOK_pin, HIGH);
    delayMicroseconds(500);
   digitalWrite(CLCOK_pin, LOW);
    delayMicroseconds(500);
}
void latch_enable(void)
   {
    digitalWrite(LATCH_pin, HIGH);
    delayMicroseconds(500);
    digitalWrite(LATCH_pin, LOW);
    }
void send_data(unsigned int data_out)
{
    int i;
    unsigned hold;
    for (i=0 ; i<8 ; i++)
    {
        if ((data_out >> i) & (0x01))
        digitalWrite(DATA_pin,HIGH); 
        else
        digitalWrite(DATA_pin,LOW); 
        
        clock_signal();
    }
    latch_enable(); // Data finally submitted
}

void setup() 
{
  pinMode(LATCH_pin , OUTPUT);
  pinMode(DATA_pin , OUTPUT);  
  pinMode(CLCOK_pin , OUTPUT);
  digitalWrite(LATCH_pin, LOW);      // (11) ST_CP [RCK] on 74HC595
  digitalWrite(CLCOK_pin, LOW);      // (9) SH_CP [SCK] on 74HC595
  digitalWrite(DATA_pin, LOW);     // (12) DS [S1] on 74HC595
  Serial.begin(9600);
}

void loop() 
{
  
        send_data(0b00000000);
        delay(1000);
        send_data(0b10000000);
        delay(1000);
        send_data(0b01000000);
        delay(1000);
        send_data(0b00100000);
        delay(1000);
        send_data(0b00010000);
        delay(1000);
        send_data(0b00001000);
        delay(1000);
        send_data(0b00000100);
        delay(1000);
        send_data(0b00000010);
        delay(1000);
        send_data(0b00000001);
        delay(1000);
}