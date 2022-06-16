#include <Braccio.h>
#include <Servo.h>

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_ver;
Servo wrist_rot;
Servo gripper;

void setup() {
  // put your setup code here, to run once:
  Braccio.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  Braccio.ServoMovement(20, 90, 90, 90, 90, 90, 73);
}
