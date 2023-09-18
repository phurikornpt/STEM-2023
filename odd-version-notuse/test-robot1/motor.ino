
#include "setup_pin_Robot_DrSup.h"


void motorL(int pwm) {
  if (pwm == 0) {
    digitalWrite (M1_INA, 0);
    digitalWrite (M1_INB, 0);
    analogWrite (M1_PWM, 255);
  } else if (pwm > 0) {
    if (pwm >= Maxspeedmotor)pwm = Maxspeedmotor;
    digitalWrite (M1_INA, 1);
    digitalWrite (M1_INB, 0);
    analogWrite (M1_PWM, pwm );
  } else if (pwm < 0) {
    if (pwm <= -Maxspeedmotor)pwm = -Maxspeedmotor;
    digitalWrite (M1_INA, 0);
    digitalWrite (M1_INB, 1);
    analogWrite (M1_PWM, -pwm );

  }
}

void motorR(int pwm) {
  if (pwm == 0) {
    digitalWrite (M2_INA, 0);
    digitalWrite (M2_INB, 0);
    analogWrite (M2_PWM, 255);
  } else if (pwm > 0) {
    
    if (pwm >= Maxspeedmotor)pwm = Maxspeedmotor;

    digitalWrite (M2_INA, 1);
    digitalWrite (M2_INB, 0);
    analogWrite (M2_PWM, pwm );
  } else if (pwm < 0) {
    if (pwm <= -Maxspeedmotor)pwm = -Maxspeedmotor;
    digitalWrite (M2_INA, 0);
    digitalWrite (M2_INB, 1);
    analogWrite (M2_PWM, -pwm );

  }
}
