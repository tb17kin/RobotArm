#include <Braccio.h>
#include <Servo.h>

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_ver;
Servo wrist_rot;
Servo gripper;

int m1 = 0;
int m2 = 0;
float m3;
int m4 = 0;
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
  m1 = 0;
  m2 = 102;
  m3 = 108;
  m4 = 83;
  m5 = 85;
  m6 = 30;
  
  Braccio.begin();

  Serial.begin(9600);
}

void loop() {

  unsigned long currentTime = millis();

    if(Serial.available() > 0){
      line = Serial.readStringUntil('\n');
      int index = line.indexOf(';');
      String sta = line.substring(0, index);
      if(sta.equals(String('S'))) {
        line.remove(0, index + 1);
        int index_m3 = line.indexOf(';');
        String str_m3 = line.substring(0, index_m3);
        line.remove(0, index_m3 + 1);
        int index_m5 = line.indexOf(';');
        String str_m5 = line.substring(0, index_m5);
        m3 = str_m3.toFloat();
        m5 = str_m5.toFloat();
      }
    }
    // 第３関節(m4)の動き
    Braccio.ServoMovement(20, m1, m2, m3, m4, m5, m6);
}
