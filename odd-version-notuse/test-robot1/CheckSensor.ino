
#include "setup_pin_Robot_DrSup.h"


unsigned int Max_Sensordata[5]={820, 570,610,758, 582};
unsigned int Min_Sensordata[5]={55 ,50 ,42 ,43, 45};

unsigned int Mid_Sensor1=((Max_Sensordata[0]-Min_Sensordata[0])/2)+Min_Sensordata[0];
unsigned int Mid_Sensor2=((Max_Sensordata[1]-Min_Sensordata[1])/2)+Min_Sensordata[1];
unsigned int Mid_Sensor3=((Max_Sensordata[2]-Min_Sensordata[2])/2)+Min_Sensordata[2];
unsigned int Mid_Sensor4=((Max_Sensordata[3]-Min_Sensordata[3])/2)+Min_Sensordata[3];
unsigned int Mid_Sensor5=((Max_Sensordata[4]-Min_Sensordata[4])/2)+Min_Sensordata[4];
/*
  max = 100 , min = 50 , Find mid = ?
  mid = ( (max - min) / 2) + min
  mid = ( (100 - 50) / 2) + 50
  mid = 75
*/
int Hysteresis_Sensor=40;

void Check_Sensor()
{ 
  Data_Sensor1 = analogRead(Sensor1);
  Data_Sensor2 = analogRead(Sensor2);
  Data_Sensor3 = analogRead(Sensor3);
  Data_Sensor4 = analogRead(Sensor4);
  Data_Sensor5 = analogRead(Sensor5);
  
  if (Data_Sensor1 > Mid_Sensor1 + Hysteresis_Sensor) Logic_Sensor1 = 0;
  else if (Data_Sensor1 < Mid_Sensor1 - Hysteresis_Sensor) Logic_Sensor1 = 1;
  if (Data_Sensor2 > Mid_Sensor2 + Hysteresis_Sensor) Logic_Sensor2 = 0;
  else if (Data_Sensor2 < Mid_Sensor2 - Hysteresis_Sensor) Logic_Sensor2 = 1;
  if (Data_Sensor3 > Mid_Sensor3 + Hysteresis_Sensor) Logic_Sensor3 = 0;
  else if (Data_Sensor3 < Mid_Sensor3 - Hysteresis_Sensor) Logic_Sensor3 = 1;
  if (Data_Sensor4 > Mid_Sensor4 + Hysteresis_Sensor) Logic_Sensor4 = 0;
  else if (Data_Sensor4 < Mid_Sensor4 - Hysteresis_Sensor) Logic_Sensor4 = 1;
  if (Data_Sensor5 > Mid_Sensor5 + Hysteresis_Sensor) Logic_Sensor5 = 0;
  else if (Data_Sensor5 < Mid_Sensor5 - Hysteresis_Sensor) Logic_Sensor5 = 1;

}









