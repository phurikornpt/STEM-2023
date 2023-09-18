/*
  Inno Robot KMUTNB 
  This file for make function for Output only
*/
#include "PinZone.h"

#define gain1 0.3  //check line lavel 1
#define gain2 0.5  //check line lavel 2
#define gain3 0.7  //check line lavel 3

int Robot_position = 0;

void tracker_line_basic(int speedx) {
  /*check sensor determine digital_sensor[All] */
  getSensor();

  if (digital_sensor2 == 0 && digital_sensor3 == 0 && digital_sensor4 == 0) {
    Robot_position = 0;
    motorR(speedx);
    motorL(speedx);
  } else if (digital_sensor2 == 1 && digital_sensor3 == 0 && digital_sensor4 == 1) {
    Robot_position = 0;
    motorR(speedx);
    motorL(speedx);
  } else if (digital_sensor2 == 1 && digital_sensor3 == 0 && digital_sensor4 == 0) {
    Robot_position = 1;
    motorR(speedx * gain1);
    motorL(speedx);
  } else if (digital_sensor2 == 1 && digital_sensor3 == 1 && digital_sensor4 == 0) {
    Robot_position = 1;
    motorR(speedx * gain2);
    motorL(speedx * gain3);
  } else if (digital_sensor2 == 0 && digital_sensor3 == 0 && digital_sensor4 == 1) {
    Robot_position = 2;
    motorR(speedx);
    motorL(speedx * gain1);
  } else if (digital_sensor2 == 0 && digital_sensor3 == 1 && digital_sensor4 == 1) {
    Robot_position = 2;
    motorR(speedx * gain3);
    motorL(speedx * gain2);
  } else {
    if (Robot_position == 1) {
      motorR(0);
      motorL(speedx * gain3);
    } else if (Robot_position == 2) {
      motorL(0);
      motorR(speedx * gain3);
    } else {
      motorR(100);
      motorL(100);
    }
  }
}


// PID ZONE
int error = 0;
double kp = 2, ki = 0, kd = 20;
int sumError, preError;
void tracker_line_PID(int speedx) {
  getSensor();
  int error_1 = 5;
  int error_2 = 10;

  if (digital_sensor2 == 1 && digital_sensor3 == 0 && digital_sensor4 == 1) {
    error = 0;
  } else if (digital_sensor2 == 1 && digital_sensor3 == 0 && digital_sensor4 == 0) {
    error = error_1;
  } else if (digital_sensor2 == 1 && digital_sensor3 == 1 && digital_sensor4 == 0) {
    error = error_2;
  } else if (digital_sensor2 == 0 && digital_sensor3 == 0 && digital_sensor4 == 1) {
    error = -error_1;
  } else if (digital_sensor2 == 0 && digital_sensor3 == 1 && digital_sensor4 == 1) {
    error = -error_2;
  } else if (digital_sensor2 == 1 && digital_sensor3 == 1 && digital_sensor4 == 1) {
    error = preError;
  }


  int speed = (kp * error) + (ki * sumError) + (kd * (error - preError));
  int leftSpeed = speedx + speed;
  int rightSpeed = speedx - speed;
  int Maxspeedmotor = 100;
  if (leftSpeed > Maxspeedmotor) leftSpeed = Maxspeedmotor;
  if (rightSpeed > Maxspeedmotor) rightSpeed = Maxspeedmotor;

  if (leftSpeed < -Maxspeedmotor) leftSpeed = -Maxspeedmotor;
  if (rightSpeed < -Maxspeedmotor) rightSpeed = -Maxspeedmotor;

  motorL(leftSpeed);
  motorR(rightSpeed);

  Serial.print(leftSpeed);
  Serial.print(rightSpeed);
  Serial.println("");
  preError = error;

  if (error == 0) {
    sumError = 0;
  } else {
    sumError += error;
  }
}
void spinFontSensor_with_timer(int speed) {
  int spinline = 0;
  unsigned long counter = millis();
  while (1) {
    getSensor();
    if (millis() - counter > 20) {
      motorR(0);
      motorL(0);
      break;
    }
    if (digital_sensor2 == 0 || digital_sensor3 == 0 || digital_sensor4 == 0) {
      counter = millis();
    }
    motorR(-speed);
    motorL(speed);
  }
  counter = millis();
  while (1) {
    getSensor();
    motorR(-speed);
    motorL(speed);
    if (digital_sensor2 == 1 && digital_sensor3 == 1 && digital_sensor4 == 1) {
      counter = millis();
    }
    if (millis() - counter > 10) {
      motorR(0);
      motorL(0);
      break;
    }
  }
}
void spinFontSensor_with_deboud(int speed) {
  int spinline = 0;
  int spinline_deboud = 20;
  motorR(-speed);
  motorL(speed);
  delay(200);
  while (1) {
    getSensor();
    if (spinline >= spinline_deboud) {
      spinline = 0;
      motorR(0);
      motorL(0);
      break;
    }

    if (digital_sensor2 == 1 && digital_sensor3 == 1 && digital_sensor4 == 1) {
      spinline++;
    } else {
      spinline = 0;
    }
    motorR(-speed);
    motorL(speed);
  }

  while (1) {
    getSensor();
    motorR(-speed);
    motorL(speed);
    if (digital_sensor2 == 1 && (digital_sensor3 == 0 || digital_sensor4 == 0)) {
      spinline++;
    } else if ((digital_sensor2 == 0 || digital_sensor3 == 0) && digital_sensor4 == 1) {
      spinline++;
    } else {
      spinline = 0;
    }
    if (spinline >= 3) {
      motorR(0);
      motorL(0);
      break;
    }
  }
}
void spinMidSensor_with_deboud(int speed) {
  int spinline = 0;
  int spinline_deboud = 20;
  motorR(-speed);
  motorL(speed);
  delay(200);
  while (1) {
    getSensor();
    if (spinline >= spinline_deboud) {
      spinline = 0;
      motorR(0);
      motorL(0);
      break;
    }
    if (digital_sensor1 == 1 && digital_sensor5 == 1) spinline++;
    else spinline = 0;
    motorR(-speed);
    motorL(speed);
    delay(1);
  }
  while (1) {
    getSensor();
    motorR(-speed);
    motorL(speed);
    if (digital_sensor1 == 0 || digital_sensor5 == 0) spinline++;
    else if (digital_sensor1 == 0 || digital_sensor5 == 0) spinline++;
    else spinline = 0;

    if (spinline >= 3) {
      motorR(0);
      motorL(0);
      break;
    }
    delay(1);
  }
}

void spinFontSensor(int speed, char direct) {
  switch (direct) {
    case 'L':
      spinFontSensor_with_deboud(-speed);
      break;
    case 'R':
      spinFontSensor_with_deboud(speed);
      break;
  }
}
void spinMidSensor(int speed, char direct) {
  switch (direct) {
    case 'L':
      spinMidSensor_with_deboud(-speed);
      break;
    case 'R':
      spinMidSensor_with_deboud(speed);
      break;
  }
}


void moveToLine_with_midSensor(int speedx, int count) {
  unsigned long counter = millis();
  int linecount = 0;
  int debount_inline = 0;
  snappish_motor(speedx, 150);
  while (1) {
    getSensor();
    if (linecount >= count) {
      motorL(0);
      motorR(0);
      break;
    }

    if ((digital_sensor1 == 0 || digital_sensor5 == 0) && millis() - counter > 300) {
      debount_inline += 1;
    } else {
      debount_inline = 0;
    }

    if (debount_inline > 3) {
      linecount++;
      counter = millis();
      debount_inline = 0;
    }
    // tracker_line_basic(speedx);
    tracker_line_PID(speedx);
  }
}
void moveToLine_with_FontSensor(int speedx, int count) {
  unsigned long counter = millis();
  int linecount = 0;
  int debount_inline = 0;
  snappish_motor(speedx, 150);
  while (1) {
    getSensor();
    if (linecount >= count) {
      motorL(0);
      motorR(0);
      break;
    }

    if ((digital_sensor2 == 0 && digital_sensor4 == 0) && millis() - counter > 300) {
      debount_inline += 1;
    } else {
      debount_inline = 0;
    }

    if (debount_inline > 3) {
      linecount++;
      counter = millis();
      debount_inline = 0;
    }
    tracker_line_basic(speedx);
  }
}

void moveFind_line(int speedx) {
  getSensor();
  while (digital_sensor2 == 1 && digital_sensor3 == 1 && digital_sensor4 == 1) {
    getSensor();
    motorR(speedx);
    motorL(speedx);
  }
  motorR(0);
  motorL(0);
}
void moveToCross(int speed) {
  motorR(speed);
  motorL(speed);
  delay(200);
  while (1) {
    getSensor();
    if (digital_sensor1 == 0 || digital_sensor5 == 0) break;
  }
  motorR(0);
  motorL(0);
}

void moveToKeep_Object(int speed) {
  moveToLine_with_midSensor(speed, 1);
  myservo.write(servoKeep);
}
void moveToLeave_Object(int speed) {
  moveToLine_with_FontSensor(speed, 1);
  snappish_motor(-speed, 100);
  myservo.write(servoLeave);
  moveToCross(-speed);
}

void snappish_motor(int speed, int time_delay) {
  if (speed > 0) {
    motorR(100);
    motorL(100);
  } else {
    motorR(-100);
    motorL(-100);
  }
  delay(time_delay);
  motorR(0);
  motorL(0);
}


void motorL(int pwm) {
  int output = map(pwm, 0, 100, 0, 255);
  if (output == 0) {
    digitalWrite(pinM1_INA, 1);
    digitalWrite(pinM1_INB, 1);
  } else if (output > 0) {
    digitalWrite(pinM1_INA, 0);
    digitalWrite(pinM1_INB, 1);
  } else if (output < 0) {
    digitalWrite(pinM1_INA, 1);
    digitalWrite(pinM1_INB, 0);
  }
  analogWrite(pinM1_PWM, abs(output));
}
void motorR(int pwm) {
  int output = map(pwm, 0, 100, 0, 255);
  if (output == 0) {
    digitalWrite(pinM2_INA, 1);
    digitalWrite(pinM2_INB, 1);
  } else if (output > 0) {
    digitalWrite(pinM2_INA, 0);
    digitalWrite(pinM2_INB, 1);
  } else if (output < 0) {
    digitalWrite(pinM2_INA, 1);
    digitalWrite(pinM2_INB, 0);
  }
  analogWrite(pinM2_PWM, abs(output));
}

void setup_outputBot() {
  pinMode(pinM1_INA, OUTPUT);
  pinMode(pinM1_INB, OUTPUT);
  pinMode(pinM1_PWM, OUTPUT);
  pinMode(pinM2_INA, OUTPUT);
  pinMode(pinM2_INB, OUTPUT);
  pinMode(pinM2_PWM, OUTPUT);


  pinMode(pinLed1, OUTPUT);
  pinMode(pinLed2, OUTPUT);
  pinMode(pinLed3, OUTPUT);
  pinMode(pinLed4, OUTPUT);
  pinMode(pinLed5, OUTPUT);
  pinMode(pinLed6, OUTPUT);
}
