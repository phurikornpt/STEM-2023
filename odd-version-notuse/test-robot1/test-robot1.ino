////------------- Include library ------------------

#include <Servo.h>
#include "setup_pin_Robot_DrSup.h"


#define slow1 0.8  //check line lavel 1
#define slow2 0     //check line lavel 2
#define slow3 0.85  //check line lavel 2

#define Spin_speed 90
#define spinline_deboud 20


#define Gipper_Lock 0
#define Gipper_UnLock 65

#define SpeedML 1
#define SpeedMR 1
///-------------- setup initial value ------------------
Servo myservo1;
//Servo myservo2;
int i = 0, linecount = 0, linecheck = 0, Robot_position = 0;
int debount = 0;
int mission = 0;
int debount_in = 0;

int speed1 = 150;
unsigned long RAW_Time = 0, mint_1 = 0, mint_1_30 = 0, mint_2 = 0, timeStart = 0;

unsigned int Data_Sensor1 = 0;
unsigned int Data_Sensor2 = 0;
unsigned int Data_Sensor3 = 0;
unsigned int Data_Sensor4 = 0;
unsigned int Data_Sensor5 = 0;

boolean Logic_Sensor1 = 0;
boolean Logic_Sensor2 = 0;
boolean Logic_Sensor3 = 0;
boolean Logic_Sensor4 = 0;
boolean Logic_Sensor5 = 0;

void setup() {
  Serial.begin(9600);
  pinMode(M1_INA, OUTPUT);
  pinMode(M1_INB, OUTPUT);
  pinMode(M1_PWM, OUTPUT);
  pinMode(M2_INA, OUTPUT);
  pinMode(M2_INB, OUTPUT);
  pinMode(M2_PWM, OUTPUT);
  pinMode(Sensor1, INPUT);
  pinMode(Sensor2, INPUT);
  pinMode(Sensor3, INPUT);
  pinMode(Sensor4, INPUT);
  pinMode(Sensor5, INPUT);
  pinMode(Sensor_Object, INPUT);

  pinMode(SW1, INPUT_PULLUP);
  pinMode(T_LED6, OUTPUT);
  pinMode(SW2, INPUT_PULLUP);

  myservo1.attach(Servo1);
  myservo1.write(Gipper_UnLock);
}

void loop() {
  // GetSensor_Analog();
  GetSensor_Digital();
  // motorL(255);
  motorR(255);
  /*
  while (1) {
    if (digitalRead(SW1) == 0) {
      // ปุ่มที่ 1

      move_withMid(150, 1, ' ');
      motorL(0);
      motorR(0);
    }
    if (digitalRead(SW2) == 0) {
      // ปุ่มที่ 1

      Example_point_1();
    }
  }
  while (1) {
    Check_Sensor();
    Serial.print("Sensor = ");
    Serial.print(Logic_Sensor1);
    Serial.print(Logic_Sensor2);
    Serial.print(Logic_Sensor3);
    Serial.print(Logic_Sensor4);
    Serial.println(Logic_Sensor5);

    if (digitalRead(SW1) == 0) {
      // ปุ่มที่ 1
      move_withEdge(120 , 3 , 'R');
      move_withEdge(120 , 3 , ' ');
      keep_Object(120);
      spin_withMid(120 , 2 , 'L');
      move_withEdge(120 , 3 , 'R');
      place_Object(120);

      // place_Object(120);
        // move_withEdge(110, 4 , 'R');
        // move_withEdge(110, 1 , ' ');
        // motorR(0);
        // motorL(0);

    }
    if (digitalRead(SW2) == 0) {
      // ปุ่มที่ 2
      Example_point_1();
      // move_withEdge(120, 1, ' ');
      // keep_Object(120);
    }
  }*/
}

void GetSensor_Digital() {
  Check_Sensor();
  Serial.print("Sensor = ");
  Serial.print(Logic_Sensor1);
  Serial.print(Logic_Sensor2);
  Serial.print(Logic_Sensor3);
  Serial.print(Logic_Sensor4);
  Serial.println(Logic_Sensor5);
  delay(100);
}
void GetSensor_Analog() {
  Check_Sensor();
  Serial.print("Sensor = ");
  Serial.print(Data_Sensor1);
  Serial.print(" ");
  Serial.print(Data_Sensor2);
  Serial.print(" ");
  Serial.print(Data_Sensor3);
  Serial.print(" ");
  Serial.print(Data_Sensor4);
  Serial.print(" ");
  Serial.println(Data_Sensor5);
  delay(100);
}
void Example_point_1() {
  int speeding = 150;
  move_withEdge(speeding, 3, 'R');
  move_withEdge(speeding, 3, 'L');
  move_withEdge(speeding, 1, 'R');
  keep_Object(110);
  move_withEdge(speeding, 0, 'R');
  move_withEdge(speeding, 3, 'R');
  place_Object(110);
}

void spin_withMid(int sp, int num, char turn) {
  if (turn == 'L') {
    sp = -sp;
  } else if (turn == 'R') {
    sp = sp;
  }
  for (int i = 1; i <= num; i++) {
    spin(sp);
  }
}

void spin_withEdge(int sp, int num, char turn) {
  if (turn == 'L') {
    sp = -sp;
  } else if (turn == 'R') {
    sp = sp;
  }
  for (int i = 1; i <= num; i++) {
    spin2(sp);
  }
}

void keep_Object(int sp)  //วิ่งไปหยิบชิ้นงานแล้วหุ่นจะจอดที่จุดวางชิ้นงาน
{
  move_withEdge(sp, 1, ' ');
  motorR(0);
  motorL(0);
  myservo1.write(Gipper_Lock);  //////90หนีบ 130ปล่อย
  delay(200);
}
void place_Object(int sp) {  //วิ่งไปวางชิ้นงาน เเล้วถอยหลังมา 1 เส้นตัด
  move_withMid(sp, 1, ' ');
  motorL(0);
  motorR(0);
  delay(500);
  myservo1.write(Gipper_UnLock);
  back_with_Mid();
}

void move_withEdge(int sp, int line, char turn) {
  if (line != 0) move_line5_countV2(sp, line);
  if (turn == 'L') {
    spin(-100);
  } else if (turn == 'R') {
    spin(100);
  }
}
void move_withMid(int sp, int line, char turn) {
  if (line != 0) move_line5_countV3(sp, line);
  if (turn == 'L') {
    spin(-100);
  } else if (turn == 'R') {
    spin(100);
  }
}