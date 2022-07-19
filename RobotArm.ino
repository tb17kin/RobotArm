#include <Servo.h>
#include <Arduino_JSON.h>

String flag = "A";
int u1;
int u2;

int PULSE_WIDTH_m3;
int PULSE_WIDTH_m5;
const int PIN_m3 = 9;
const int PIN_m5 = 5;
const int PIN = 12;

// 時刻のミリ秒の測定
unsigned long previousTime = 0;

void setup() {

  Serial.begin(9600);

  pinMode(PIN, OUTPUT);
  pinMode(PIN_m3, OUTPUT);
  pinMode(PIN_m5, OUTPUT);
  digitalWrite(PIN, HIGH);
}

void loop() {
  unsigned long currentTime = millis();

  if(currentTime - previousTime > 500){
    Serial.println(flag);
    delay(50);
    SendValue();
    previousTime = currentTime;
  }

}

void SendValue(){
  String line = Serial.readStringUntil('\n');
  JSONVar obj = JSON.parse(line);
  u1 = obj["u1"];
  u2 = obj["u2"];
  PULSE_WIDTH_m3 = map(u1, 0, 180, 500, 2400);
  PULSE_WIDTH_m5 = map(u2, 0, 180, 500, 2400);
  digitalWrite(PIN_m3, HIGH);
  delayMicroseconds(PULSE_WIDTH_m3);
  digitalWrite(PIN_m3, LOW);
  digitalWrite(PIN_m5, HIGH);
  delayMicroseconds(PULSE_WIDTH_m5);
  digitalWrite(PIN_m5, LOW);
}
