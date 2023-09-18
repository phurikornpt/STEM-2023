/*
  Inno Robot KMUTNB 
  This file for write code control logic
*/

#include "PinZone.h"
#include <Servo.h>
Servo myservo;

void setup() {
  Serial.begin(9600);

  pinMode(pinM1_INA, OUTPUT);
  pinMode(pinM1_INB, OUTPUT);
  pinMode(pinM1_PWM, OUTPUT);
  pinMode(pinM2_INA, OUTPUT);
  pinMode(pinM2_INB, OUTPUT);
  pinMode(pinM2_PWM, OUTPUT);
  pinMode(pinSensor1, INPUT);
  pinMode(pinSensor2, INPUT);
  pinMode(pinSensor3, INPUT);
  pinMode(pinSensor4, INPUT);
  pinMode(pinSensor5, INPUT);

  pinMode(pinSw1, INPUT_PULLUP);
  pinMode(pinSw2, INPUT_PULLUP);

  pinMode(pinLed1, OUTPUT);
  pinMode(pinLed2, OUTPUT);
  pinMode(pinLed3, OUTPUT);
  pinMode(pinLed4, OUTPUT);
  pinMode(pinLed5, OUTPUT);
  pinMode(pinLed6, OUTPUT);

  myservo.attach(pinServo);
  myservo.write(servoKeep);


}

void loop() {
  // tryLed();
  // tryMotorSequence();
  // tryMotorL('B');
  // tryMotorR('B');
  // delay(100);
  // tryServo();
}

void tryServo(){
  myservo.write(servoKeep);
  delay(1000);
  myservo.write(servoLeave);
  delay(1000);
}
void tryMotorSequence() {
  tryMotorL('F');
  tryMotorR('F');
  delay(1000);
  tryMotorL('B');
  tryMotorR('B');
  delay(1000);
  tryMotorL('S');
  tryMotorR('S');
  delay(1000);
}
void tryMotorL(char con) {
  switch (con) {
    case 'F':
      motorL(100);
      break;
    case 'B':
      motorL(-100);
      break;
    case 'S':
      motorL(0);
      break;
  }
}
void tryMotorR(char con) {
  switch (con) {
    case 'F':
      motorR(100);
      break;
    case 'B':
      motorR(-100);
      break;
    case 'S':
      motorR(0);
      break;
  }
}



void tryLed() {
  int led[] = { pinLed1, pinLed2, pinLed3, pinLed4, pinLed5, pinLed6 };
  int time = 300;
  for (int i = 0; i < 6; i++) {
    digitalWrite(led[i], HIGH);
    delay(time);
  }
  for (int i = 0; i < 6; i++) {
    digitalWrite(led[i], LOW);
    delay(time);
  }
}
