
#include "setup_pin_Robot_DrSup.h"


void tracker_line(int speedx)
{
  /*check sensor determine Logic_sensor[All] */
  Check_Sensor();

  if (Logic_Sensor2 == 0 && Logic_Sensor3 == 0 && Logic_Sensor4 == 0)
  {
    Robot_position = 0;
    motorR(speedx);
    motorL(speedx);
  }
  else if (Logic_Sensor2 == 1 && Logic_Sensor3 == 0 && Logic_Sensor4 == 1)
  {
    Robot_position = 0;
    motorR(speedx);
    motorL(speedx);
  }
  else if (Logic_Sensor2 == 1 && Logic_Sensor3 == 0 && Logic_Sensor4 == 0)
  {
    Robot_position = 1;
    motorR(speedx * slow1);
    motorL(speedx);
  }
  else if (Logic_Sensor2 == 1 && Logic_Sensor3 == 1 && Logic_Sensor4 == 0)
  { Robot_position = 1;
    motorR(speedx * slow2);
    motorL(speedx * slow3);
  }
  else if (Logic_Sensor2 == 0 && Logic_Sensor3 == 0 && Logic_Sensor4 == 1)
  {
    Robot_position = 2;
    motorR(speedx);
    motorL(speedx * slow1);
  }
  else if (Logic_Sensor2 == 0 && Logic_Sensor3 == 1 && Logic_Sensor4 == 1)
  {
    Robot_position = 2;
    motorR(speedx * slow3);
    motorL(speedx * slow2);
  }
  else {
    if (Robot_position == 1) {
      motorR(0);
      motorL(speedx * slow3);
    } else if (Robot_position == 2) {
      motorL(0);
      motorR(speedx * slow3);
    } else {
      motorR(100);
      motorL(100);
    }
  }
}

void spin(int speed)
{
  int spinline = 0;

  motorR(-speed);
  motorL(speed);
  delay(200);

  while (1)
  { 
      Check_Sensor();
      if (spinline >= spinline_deboud)
      { 
          spinline = 0;
          motorR(0);
          motorL(0);
          break;
      }

      if (Logic_Sensor2 == 1 && Logic_Sensor3 == 1 && Logic_Sensor4 == 1){
          spinline++;
      }else {
          spinline = 0;
      }
      motorR(-speed);
      motorL(speed);

  }

  while (1)
  {
      Check_Sensor();
      motorR(-speed);
      motorL(speed);
      if (Logic_Sensor2 == 1 && (Logic_Sensor3 == 0 || Logic_Sensor4 == 0)){
          spinline++;
      }else if ((Logic_Sensor2 == 0 || Logic_Sensor3 == 0) && Logic_Sensor4 == 1){
          spinline++;
      }else {
          spinline = 0;
      }

      if (spinline >= 2)
      { 
          motorR(0);
          motorL(0);
          break;
      }
  }

  
}

void spin2(int speed)// use RL sensor
{
  int spinline = 0;
  motorR(-speed);
  motorL(speed);
  delay(200);

  while (1)
  { 
    Check_Sensor();
    if (spinline >= spinline_deboud)
    { spinline = 0;
      motorR(0);
      motorL(0);
      break;
    }
    if (Logic_Sensor1 == 1 && Logic_Sensor5 == 1)spinline++;
    else spinline = 0;
    motorR(-speed);
    motorL(speed);
    delay(1);
  }
  while (1)
  { Check_Sensor();
    motorR(-speed);
    motorL(speed);
    if (Logic_Sensor1 == 0 || Logic_Sensor5 == 0 )spinline++;
    else if (Logic_Sensor1 == 0 || Logic_Sensor5 == 0)spinline++;
    else spinline = 0;

    if (spinline >= 2)
    { motorR(0);
      motorL(0);
      break;

    }
    delay(1);
  }
}




void move_line5_countV2(int speedx, int count)
{
  long incout = 0, incout_T = 0;
  linecount = 0;
  linecheck = 0;
  debount = 0;
  int gg = 1;
  incout_T = millis();
  while (1)
  {
    Check_Sensor();
    if (linecount >= count)break;


    if ((Logic_Sensor1 == 0 || Logic_Sensor5 == 0) && millis() - incout_T > 400) //เจอเส้นตัด จะเช็คเมื่อผ่านไป 400 mS
    {
      debount_in++;
    }
    else
    {
      debount_in--;
      if (debount_in < 0)debount_in = 0;
    }
    if (debount_in > 7)//เจอเส้นตัดนานพอไหม
    {
      if (gg == 1) {
        linecount++;//นับเส้นตัด
        gg = 0;
      }
      debount_in = 8;
      linecheck = 1;
      debount = 0;
    }
    else //เลยเส้นตัดไปแล้ว
    {
      if (linecheck == 1)
      {
        debount++;
        Serial.print("debount");
        Serial.println(debount);
      }
      else
      {
        debount = 0;
      }
      if (linecheck == 1 && debount >= 1)//เช็คว่าเลยเส้นตัดไปนานพอหรือยัง
      { //Serial.print("debount = 2");
        linecheck = 0;
        // linecount++;
        incout_T = millis();
        gg = 1;
        Serial.print("linecount");
        Serial.println(linecount);
        debount = 0;
      }
    }
    /////////////////////--------------------tracker_line-----------------------------------
    tracker_line(speedx);
  }
}
void move_line5_countV3(int speedx, int count)
{
  long incout = 0, incout_T = 0;
  linecount = 0;
  linecheck = 0;
  debount = 0;
  int gg = 1;

  while (1)
  {
    Check_Sensor();
    if (linecount >= count)break;
    if ((Logic_Sensor2 == 0 && Logic_Sensor4 == 0))//เจอเส้นตัด จะเช็คเมื่อผ่านไป 400 mS
    {
      debount_in++;
    }
    else
    {
      debount_in--;
      if (debount_in < 0)debount_in = 0;
    }
    if (debount_in > 7)//เจอเส้นตัดนานพอไหม
    {
      if (gg == 1) {
        linecount++;//นับเส้นตัด
        gg = 0;
      }
      debount_in = 8;
      linecheck = 1;
      debount = 0;
    }
    else //เลยเส้นตัดไปแล้ว
    {
      if (linecheck == 1)
      {
        debount++;
        Serial.print("debount");
        Serial.println(debount);
      }
      else
      {
        debount = 0;
      }
      if (linecheck == 1 && debount >= 1)//เช็คว่าเลยเส้นตัดไปนานพอหรือยัง
      { //Serial.print("debount = 2");
        linecheck = 0;
        //linecount++;
        gg = 1;
        Serial.print("linecount");
        Serial.println(linecount);
        debount = 0;
      }
    }
    /////////////////////--------------------tracker_line-----------------------------------
    tracker_line(speedx);
  }
}


// วิ่งหาเส้น เเล้วไปต่อ
void Move_to_line(int speedx)
{ 
  Check_Sensor();
  while (Logic_Sensor2 == 1 && Logic_Sensor3 == 1 && Logic_Sensor4 == 1)
  { Check_Sensor();
    motorR(speedx);
    motorL(speedx );
  }
}

// ถอยหลังจน S1 and S5 เจอเส้น เเล้วหยุด
void back_with_Mid(){
    motorR(-150);
    motorL(-150);
    while (1)
    { Check_Sensor();
      if (Logic_Sensor1 == 0 || Logic_Sensor5 == 0)break;
    }
    motorR(0);
    motorL(0);
}
//  track เส้น จนไม่เจอเส้นเลย เเล้วหยุด
void go_To_outline(){
    motorR(120);
    motorL(120);
    while (1){ 
        Check_Sensor();
        tracker_line(120);
        if (Logic_Sensor2 == 1 && Logic_Sensor3 == 1 && Logic_Sensor4 == 1)break;
    }
    motorR(0);
    motorL(0);
}
// ถอยหลังเเล้วปล่อยเเท่นวาง เเล้วหยุด
void moveout()
{
  motorR(-150);
  motorL(-150);
  delay(250);
  motorR(0);
  motorL(0);
  delay(250);
  myservo1.write(Gipper_UnLock);//////90หนีบ 130ปล่อย
  delay(200);
}
void moveout2()
{
  motorR(100);
  motorL(100);
  delay(700);
  motorR(0);
  motorL(0);
  myservo1.write(Gipper_UnLock);//////90หนีบ 130ปล่อย
  delay(200);
  back_with_Mid();
  spin(200);
  spin(200);
}
void Keep_Object()//หยิบชิ้นงานแล้วหุ่นจะจอดที่จุดวางชิ้นงาน
{
  ////////////////////////////////////////////วิ่งไปจับSTART
  move_line5_countV2(150, 1);
  motorR(0);
  motorL(0);
  myservo1.write(Gipper_Lock);//////90หนีบ 130ปล่อย
  delay(100);
  // spin(200);
  //spin(200);
  ////////////////////////////////////////////วิ่งไปจับEND

}
