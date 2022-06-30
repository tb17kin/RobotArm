// #include <Braccio.h>
#include <Servo.h>

// Servo base;
// Servo shoulder;
// Servo elbow;
// Servo wrist_ver;
// Servo wrist_rot;
// Servo gripper;

int m1 = 0;
int m2 = 0;
int m3 = 0;
float m4;
float m5;
int m6 = 0;

// int flag = 0;
Servo servo;
String serial_recv;
String line;
int line_len;
const int PIN_SERVO = 10;
float val=180;
int PULSE_WIDTH;
float val_before;

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
  
  pinMode(PIN_SERVO,OUTPUT);
}

void loop() {

  unsigned long currentTime = millis();

    if(Serial.available() > 0){
        line = Serial.readStringUntil('\n');
        int index = line.indexOf(';');
        String sta = line.substring(0, index);
        if(sta.equals(String('S'))) {
          line.remove(0, index + 1);
          int index_m4 = line.indexOf(';');
          String str_m4 = line.substring(0, index_m4);
          line.remove(0, index_m4 + 1);
          int index_m5 = line.indexOf(';');
          String str_m5 = line.substring(0, index_m5);
          m4 = str_m4.toFloat();
          m5 = str_m5.toFloat();
          val = m5;
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
