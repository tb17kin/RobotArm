#include <Servo.h>
#include <Arduino_JSON.h>

String flag = "A";
int u1;
int u2;

Servo PIN_m1;
Servo PIN_m2;
Servo PIN_m3;
Servo PIN_m5;

// 時刻のミリ秒の測定
unsigned long previousTime = 0;

void setup() {

  Serial.begin(9600);

// ピンを触れるようにする
  digitalWrite(12, HIGH);
  PIN_m1.attach(11);
  PIN_m2.attach(10);
  PIN_m3.attach(9);
  PIN_m5.attach(5);
  
  PIN_m1.write(102);
  PIN_m2.write(110);
  PIN_m3.write(50);
  PIN_m5.write(120);
}

void loop() {
  // 時間管理
  unsigned long currentTime = millis();

  if(currentTime - previousTime > 500){
    Serial.println(flag); // フラグをMATLAB側に送信
    delay(50);
    SendValue(); // 受信した値をモータに指令する
    previousTime = currentTime;
  }
}

void SendValue(){
  String line = Serial.readStringUntil('\n');
  JSONVar obj = JSON.parse(line);
  u1 = obj["u1"];
  u2 = obj["u2"];
  PIN_m1.write(102);
  PIN_m2.write(110);
  PIN_m3.write(u1);
  PIN_m5.write(u2);
}
