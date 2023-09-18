/*
  Inno Robot KMUTNB 
  This file for make function for Output only
*/
#include "PinZone.h"


void motorL(int pwm) {
  int output = map(pwm, 0, 100, 0, 255);
  if (output == 0) {
    digitalWrite(pinM1_INA, 0);
    digitalWrite(pinM1_INB, 0);
    analogWrite(pinM1_PWM, 255);
  } else if (output > 0) {
    digitalWrite(pinM1_INA, 0);
    digitalWrite(pinM1_INB, 1);
    analogWrite(pinM1_PWM, output);
  } else if (output < 0) {
    digitalWrite(pinM1_INA, 1);
    digitalWrite(pinM1_INB, 0);
    analogWrite(pinM1_PWM, abs(output));
  }
}
void motorR(int pwm) {
  int output = map(pwm, 0, 100, 0, 255);
  if (output == 0) {
    digitalWrite(pinM2_INA, 0);
    digitalWrite(pinM2_INB, 0);
    analogWrite(pinM2_PWM, 255);
  } else if (output > 0) {
    digitalWrite(pinM2_INA, 0);
    digitalWrite(pinM2_INB, 1);
    analogWrite(pinM2_PWM, output);
  } else if (output < 0) {
    digitalWrite(pinM2_INA, 1);
    digitalWrite(pinM2_INB, 0);
    analogWrite(pinM2_PWM, abs(output));
  }
}
