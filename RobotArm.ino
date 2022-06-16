#include <Braccio.h>
#include <Servo.h>

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_ver;
Servo wrist_rot;
Servo gripper;

float m1;
float m2;
float m3;
float m4;
float m5;
float m6;

void setup() {
  // アームがまっすぐな位置(たぶん)
  m1 = 0;
  m2 = 102;
  m3 = 108;
  m4 = 83;
  m5 = 85;
  m6 = 30;
  
  Braccio.begin();
}

void loop() {

  // 第３関節(m4)の動き
  if(m4 == 83)
  {
    m4 = 63;
  }else if(m4 == 63){
    m4 = 73;
  }else{
    m4 = 83;
  }

  // グリッパー(m6)の開閉
  if(m6 == 60)
  {
    m6 = 30;
  }else{
    m6 = 60;
  }
  Braccio.ServoMovement(20, m1, m2, m3, m4, m5, m6);
}
