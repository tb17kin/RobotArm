#include <Braccio.h>
#include <Servo.h>
#include <Arduino_JSON.h>

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_ver;
Servo wrist_rot;
Servo gripper;

int m1;
int m2;
int m3;
int m4;
int m5;
int m6;
int t = 0;
String flag = "A";
Servo servo;

// 時刻のミリ秒の測定
unsigned long previousTime = 0;

void setup() {
  Braccio.begin();

  Serial.begin(9600);
  // アームがまっすぐな位置(たぶん)
  m1 = 0;
  m2 = 102;
  m3 = 108;
  m4 = 83;
  m5 = 85;
  m6 = 30;
  
}

void loop() {
  unsigned long currentTime = millis();
  if(currentTime - previousTime > 500){
    Serial.println(flag);
    delay(100);
    SendValue();
    previousTime = currentTime;
  }
}

void SendValue(){
  String line = Serial.readStringUntil('\n');
  JSONVar obj = JSON.parse(line);
  m3 = obj["m3"];
  m5 = obj["m5"];
  // 第３関節(m4)の動き
  Braccio.ServoMovement(20, 0, 102, m3, 83, m5, 30);
}
