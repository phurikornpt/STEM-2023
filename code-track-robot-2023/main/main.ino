/*
  Inno Robot KMUTNB 
  This file for write code control logic
*/

#include "PinZone.h"
#include <Servo.h>

/* ------------------- < Zone Variable Servo > ------------------- */
Servo myservo;



/* ------------------- < Zone Variable Sensor > ------------------- */
unsigned int analog_sensor1 = 0;
unsigned int analog_sensor2 = 0;
unsigned int analog_sensor3 = 0;
unsigned int analog_sensor4 = 0;
unsigned int analog_sensor5 = 0;

boolean digital_sensor1 = 0;
boolean digital_sensor2 = 0;
boolean digital_sensor3 = 0;
boolean digital_sensor4 = 0;
boolean digital_sensor5 = 0;

int swForward;
int swBackward;
int swLeft;
int swRight;
int swKeep;
int swLeave;

void setup() {
  Serial.begin(9600);
  setup_inputAutoBot();
  // setup_inputManualBot();
  setup_outputBot();
  myservo.attach(pinServo);
  myservo.write(servoLeave);
}

void example1() {
  moveToLine_with_midSensor(80, 1, 'L');

  moveToLine_with_midSensor(80, 3, 'N');
  moveToKeep_Object(60);


  spinFontSensor_count(60, 'R', 2);

  
  moveToLine_with_midSensor(80, 1, 'L');
  moveToLine_with_midSensor(80, 2, 'N');

  moveToLeave_Object(60);
  moveToLine_with_midSensor(80,4, 'L');
  moveToLine_with_midSensor(80,2, 'N');
  snappish_motor(100,300);
}

void loop() {

  tryToTest();

  if (digitalRead(pinSw1) == 0) {
    example1();
  }

  // if (digitalRead(pinSw2) == 0) {
  //   while (1) {
  //     break;
  //   }
  // }
}


/* ------------------- < Zone Function Manual Robot > ------------------- */
void control_manual() {
  getJoy();
  if (swForward == 0 && swBackward == 1 && swLeft == 1 && swRight == 1) {
    motorL(100);
    motorR(100);
  } else if (swForward == 1 && swBackward == 0 && swLeft == 1 && swRight == 1) {
    motorL(-100);
    motorR(-100);
  } else if (swForward == 1 && swBackward == 1 && swLeft == 0 && swRight == 1) {
    motorL(-100);
    motorR(100);
  } else if (swForward == 1 && swBackward == 1 && swLeft == 1 && swRight == 0) {
    motorL(100);
    motorR(-100);
  } else {
    motorL(0);
    motorR(0);
  }
  if (swKeep == 0 && swLeave == 1) {
    myservo.write(servoKeep);
  } else if (swKeep == 1 && swLeave == 0) {
    myservo.write(servoLeave);
  }
}


/* ------------------- < Zone Function Test Robot > ------------------- */
String state_test = "";
int value_test = 0;
void tryToTest() {
  if (Serial.available() > 0) {
    String msg = Serial.readStringUntil('\n');
    state_test = msg;
    if (msg.substring(0, 2) == "sv") {
      state_test = "sv";
      value_test = msg.substring(2, msg.length()).toInt();
    } else if (msg.substring(0, 2) == "ml" || msg.substring(0, 2) == "mr") {
      state_test = msg.substring(0, 2);
      value_test = msg.substring(2, msg.length()).toInt();
    }
  }
  if (state_test == "sa") {
    trySensor('A');
  } else if (state_test == "sd") {
    trySensor('D');
  } else if (state_test == "ml") {
    motorL(value_test);
    Serial.println("motorL  " + String(value_test));
  } else if (state_test == "mr") {
    motorR(value_test);
    Serial.println("motorR  " + String(value_test));
  } else if (state_test == "sv") {
    Serial.println("Server : " + String(value_test));
    myservo.write(value_test);
  } else if (state_test == "led") {
    tryLed();
  } else if (state_test == "sw") {
    trySwitch();
  }
}
void tryServo() {
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
void trySensor(char type) {
  switch (type) {
    case 'D':
      printSensor_Digital();
      break;
    case 'A':
      printSensor_Analog();
      break;
  }
}
void trySwitch() {
  Serial.print("Switch : ");
  Serial.print(digitalRead(pinSw1));
  Serial.print(" , ");
  Serial.println(digitalRead(pinSw2));
}
void example_A() {
  int conSpeed = 70;
  // A
  moveToLine_with_midSensor(conSpeed, 1, 'L');
  moveToLine_with_midSensor(conSpeed, 3, 'N');
  moveToKeep_Object(100);
  spinFontSensor_count(60, 'R', 2);

  moveToLine_with_midSensor(conSpeed, 1, 'L');
  moveToLine_with_midSensor(conSpeed, 2, 'N');
  moveToLeave_Object(60);
  moveToLine_with_midSensor(conSpeed, 2, 'L');

  // B
  moveToKeep_Object(80);
  spinFontSensor_count(80, 'R', 2);
  moveToLine_with_midSensor(conSpeed, 1, 'R');
  moveToLine_with_midSensor(conSpeed, 1, 'R');
  moveToLine_with_midSensor(conSpeed, 2, 'R');


  moveToLine_with_midSensor(conSpeed, 1, 'L');
  moveToLine_with_midSensor(conSpeed, 1, 'R');
  moveToLine_with_midSensor(conSpeed, 3, 'R');
  moveToLine_with_midSensor(conSpeed, 1, 'L');
  moveToLine_with_midSensor(conSpeed, 1, 'R');
  moveToLine_with_midSensor(conSpeed, 2, 'R');
  moveToLine_with_midSensor(conSpeed, 1, 'N');
  moveToLeave_Object(60);

  // C
  moveToLine_with_midSensor(conSpeed, 2, 'L');
  moveToLine_with_midSensor(conSpeed, 2, 'L');
  moveToLine_with_midSensor(conSpeed, 1, 'R');
  moveToLine_with_midSensor(conSpeed, 1, 'L');
  moveToLine_with_midSensor(conSpeed, 3, 'L');
  moveToLine_with_midSensor(conSpeed, 2, 'R');
  moveToKeep_Object(80);
  spinFontSensor_count(80, 'R', 2);
  moveToLine_with_midSensor(conSpeed, 1, 'L');
  moveToLine_with_midSensor(conSpeed, 1, 'R');

  moveToLeave_Object(60);
  moveToLine_with_midSensor(conSpeed, 1, 'L');
  moveToLine_with_midSensor(conSpeed, 4, 'N');

  // Delay Go End
  snappish_motor(100, 400);
}
