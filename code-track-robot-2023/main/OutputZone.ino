/*
  Inno Robot KMUTNB 
  This file for make function for Output only
*/
#include "PinZone.h"

#define gain1 0.3  //check line lavel 1
#define gain2 0.5  //check line lavel 2
#define gain3 0.7  //check line lavel 3

int Robot_position = 0;

/*------------------------------------------------------------------
  Trackline with Basic Code
  ------------------------------------------------------------------*/
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


/*------------------------------------------------------------------
  Trackline with PID Code
  PID คือระบบการควบคุมที่มองที่ Error
  Kp = การขยาย Error 
       ถ้า Kp มากจะทำให้ Robot เข้าเส้นได้เร็วขึ้น
       ถ้า Kp น้อยจะทำให้ Robot เข้าเส้นได้ช้า
  Ki = Error สะสม (ปกติในการเดินตามเส้น จะให้ Ki = 0)
       ถ้า Ki มากจะทำให้ Robot เข้าเส้นได้เร็วขึ้นทวีคูณ  !! อาจทำให้ Robot เคลื่อนที่ผิดพลาดได้
  Kd = การลดความเร็ว
       ถ้า Kd มากจะทำให้ Robotเข้าเส้นได้ช้า เเต่เคลื่อนที่ได้สมูทมาก

  หลักการจูน
  1.เริ่มที่ Kp ที่ Robot สามารถเข้าเส้นตามที่เราพอใจ
  2.ถ้าอยากให้ Robot เข้าเส้นแบบไม่เหวี่ยงจนเกินไป ให้ปรับ Kd 

  ------------------------------------------------------------------*/
int error = 0;
double kp = 8, ki = 0, kd = 1;
int sumError, preError;
void tracker_line_PID(int speedx) {
  // Get sensor
  getSensor();
  // Define Error
  int error_1 = 5;
  int error_2 = 10;

  // Condition for Error
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

  // Cal
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

/*------------------------------------------------------------------
  เหมุน Robot โดยใช้ Sensor หน้า 3ตัว เเบบจับเวลา
  ------------------------------------------------------------------*/
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

/*------------------------------------------------------------------
  เหมุน Robot โดยใช้ Sensor หน้า 3ตัว เเบบใช้หลักนับจำนวนรอบการเข้า
  ------------------------------------------------------------------*/
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

/*------------------------------------------------------------------
  เหมุน Robot โดยใช้ Sensor กลาง 2ตัว เเบบใช้หลักนับจำนวนรอบการเข้า
  ------------------------------------------------------------------*/
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


/*------------------------------------------------------------------
  หมุน Robot โดยใช้ Sensor หน้า 3ตัว เเบบแปลง Function ให้รับ (ความเร็ว , ทิศทาง)ให้ง่ายต่อการใช้
  ------------------------------------------------------------------*/
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

/*------------------------------------------------------------------
  หมุน Robot โดยใช้ Sensor กลาง 2ตัว เเบบแปลง Function ให้รับ (ความเร็ว , ทิศทาง)ให้ง่ายต่อการใช้
  ------------------------------------------------------------------*/
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

/*------------------------------------------------------------------
  หมุน Robot โดยใช้ Sensor หน้า 3ตัว เเบบแปลง Function ให้รับ (ความเร็ว , ทิศทาง , จำนวนรอบการหมุน)ให้ง่ายต่อการใช้
  ------------------------------------------------------------------*/
void spinFontSensor_count(int speed, char direct, int num) {
  for (int i = 0; i < num; i++) {
    spinFontSensor(speed, direct);
  }
}

/*------------------------------------------------------------------
  หมุน Robot โดยใช้ Sensor กลาง 2 ตัว เเบบแปลง Function ให้รับ (ความเร็ว , ทิศทาง , จำนวนรอบการหมุน)ให้ง่ายต่อการใช้
  ------------------------------------------------------------------*/
void spinMidSensor_count(int speed, char direct, int num) {
  for (int i = 0; i < num; i++) {
    spinMidSensor(speed, direct);
  }
}


/*------------------------------------------------------------------
  เดินตามเส้นของ Robot ให้นับเส้นตัด โดยใช้ Sensor กลาง 2 ตัว 
  Function ให้รับ (ความเร็ว , จำนวนเส้นตัด , ทิศทาง) -> ทิศทาง เมื่อเคลื่อนตามจำนวนเส้นตัดเเล้วให้หมุนตามทิศทาง
  ------------------------------------------------------------------*/
void moveToLine_with_midSensor(int speedx, int count, char direction) {
  unsigned long counter = millis();
  int linecount = 0;
  int debount_inline = 0;
  snappish_motor(100, 80);
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

    if (debount_inline > 5) {
      linecount++;
      counter = millis();
      debount_inline = 0;
    }
    // tracker_line_basic(speedx);
    tracker_line_PID(speedx);
  }
  spinFontSensor(speedx, direction);
}

/*------------------------------------------------------------------
  เดินตามเส้นของ Robot ให้นับเส้นตัด โดยใช้ Sensor หน้า 2 ตัว 
  Function ให้รับ (ความเร็ว , จำนวนเส้นตัด )
  ------------------------------------------------------------------*/
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

/*------------------------------------------------------------------
  เดินหาเส้นของจนกว่า Sensor หน้า 3 ตัวเจอเส้น
  Function ให้รับ (ความเร็ว )
  ------------------------------------------------------------------*/
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


/*------------------------------------------------------------------
  ให้ Robot วิ่งไปข้างหน้า 1 เส้นตัด ด้วย Sensor กลาง 2 ตัว 
  จากนั้นหยิบชิ้นงาน
  Function ให้รับ (ความเร็ว)
  ------------------------------------------------------------------*/
void moveToKeep_Object(int speed) {
  moveToLine_with_midSensor(speed, 1, 'N');
  myservo.write(servoKeep);
}

/*------------------------------------------------------------------
  ให้ Robot วิ่งไปข้างหน้า 1 เส้นตัด ด้วย Sensor หน้า 3 ตัว 
  จากนั้นปล่อยชิ้นงาน 
  หยุดรอ 200 ms
  ถอยหลังตามความเร็ว Delay(80)
  จากนั้นหมุนขวา 1 รอบ
  Function ให้รับ (ความเร็ว)
  ------------------------------------------------------------------*/
void moveToLeave_Object(int speed) {
  moveToLine_with_FontSensor(speed, 1);
  myservo.write(servoLeave);
  delay(200);
  snappish_motor(-speed, 80);
  spinFontSensor(speed, 'R');
}


/*------------------------------------------------------------------
  ให้ Robot วิ่งเเบบหน่วงเวลา 
  Function ให้รับ (ความเร็ว , เวลา ที่ต้องการหน่วงเวลา)
  ------------------------------------------------------------------*/
void snappish_motor(int speed, int time_delay) {
  motorR(speed);
  motorL(speed);
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
