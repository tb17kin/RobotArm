// #include <Braccio.h>
#include <Servo.h>

// Servo base;
// Servo shoulder;
// Servo elbow;
// Servo wrist_ver;
// Servo wrist_rot;
// Servo gripper;

// float m1;
// float m2;
// float m3;
// float m4;
// float m5;
// float m6;

int flag = 0;
int SA = 0;
Servo servo;
String serial_recv;
String line;
int line_len;
const int LED = 13;
const int PIN_SERVO = 10;
int val=180;
int PULSE_WIDTH;
int val_before;

// 時刻のミリ秒の測定
unsigned long previousTime = 0;

void setup() {
  // アームがまっすぐな位置(たぶん)
  // m1 = 0;
  // m2 = 102;
  // m3 = 108;
  // m4 = 83;
  // m5 = 85;
  // m6 = 30;
  
  // Braccio.begin();

  Serial.begin(9600);
  
  pinMode(LED,OUTPUT);
  pinMode(PIN_SERVO,OUTPUT);
}

void loop() {

  unsigned long currentTime = millis();

    if(Serial.available() > 0){
        line = Serial.readStringUntil(';');
        line_len = line.length();
        if((line_len >= 1) && (line_len <= 3)) {
          val = line.toInt();
          Serial.println(val);
        }
        }
    if(val == 0){
        val = val_before;
      }
    PULSE_WIDTH = map(val,0,180,500,2400);
        digitalWrite(PIN_SERVO,HIGH);
        delayMicroseconds(PULSE_WIDTH);
        digitalWrite(PIN_SERVO,LOW);
    val_before = val;
    // 第３関節(m4)の動き
    // Braccio.ServoMovement(20, m1, m2, m3, m4, m5, m6);
}