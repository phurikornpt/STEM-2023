/*
  Inno Robot KMUTNB 
  This file for make function for Input only
*/
#include "PinZone.h"

/* ------------------- < Define max , min of sensor & find mid > ------------------- */
unsigned int Max_Sensordata[5] = {785  , 751 , 676 , 919 , 704 };
unsigned int Min_Sensordata[5] = {192 , 185 , 128 , 653 , 67};
// unsigned int Max_Sensordata[5] = {868  , 826 , 735 , 832 , 601};
// unsigned int Min_Sensordata[5] = { 369 , 184 , 73 , 216 , 113 };
unsigned int Mid_Sensor1 = ((Max_Sensordata[0] - Min_Sensordata[0]) / 2) + Min_Sensordata[0];
unsigned int Mid_Sensor2 = ((Max_Sensordata[1] - Min_Sensordata[1]) / 2) + Min_Sensordata[1];
unsigned int Mid_Sensor3 = ((Max_Sensordata[2] - Min_Sensordata[2]) / 2) + Min_Sensordata[2];
unsigned int Mid_Sensor4 = ((Max_Sensordata[3] - Min_Sensordata[3]) / 2) + Min_Sensordata[3];
unsigned int Mid_Sensor5 = ((Max_Sensordata[4] - Min_Sensordata[4]) / 2) + Min_Sensordata[4];

int Hysteresis_Sensor = 40;

/*
  max = 100 , min = 50 , Find mid = ?
  mid = ( (max - min) / 2) + min
  mid = ( (100 - 50) / 2) + 50
  mid = 75
*/

void getSensor() {
  analog_sensor1 = analogRead(pinSensor1);
  analog_sensor2 = analogRead(pinSensor2);
  analog_sensor3 = analogRead(pinSensor3);
  analog_sensor4 = analogRead(pinSensor4);
  analog_sensor5 = analogRead(pinSensor5);

  if (analog_sensor1 > Mid_Sensor1 + Hysteresis_Sensor) digital_sensor1 = 0;
  else if (analog_sensor1 < Mid_Sensor1 - Hysteresis_Sensor) digital_sensor1 = 1;
  if (analog_sensor2 > Mid_Sensor2 + Hysteresis_Sensor) digital_sensor2 = 0;
  else if (analog_sensor2 < Mid_Sensor2 - Hysteresis_Sensor) digital_sensor2 = 1;
  if (analog_sensor3 > Mid_Sensor3 + Hysteresis_Sensor) digital_sensor3 = 0;
  else if (analog_sensor3 < Mid_Sensor3 - Hysteresis_Sensor) digital_sensor3 = 1;
  if (analog_sensor4 > Mid_Sensor4 + Hysteresis_Sensor) digital_sensor4 = 0;
  else if (analog_sensor4 < Mid_Sensor4 - Hysteresis_Sensor) digital_sensor4 = 1;
  if (analog_sensor5 > Mid_Sensor5 + Hysteresis_Sensor) digital_sensor5 = 0;
  else if (analog_sensor5 < Mid_Sensor5 - Hysteresis_Sensor) digital_sensor5 = 1;
}
void printSensor_Digital() {
  getSensor();
  Serial.print("Digital Sensor : ");
  Serial.print(digital_sensor1);
  Serial.print(" , ");
  Serial.print(digital_sensor2);
  Serial.print(" , ");
  Serial.print(digital_sensor3);
  Serial.print(" , ");
  Serial.print(digital_sensor4);
  Serial.print(" , ");
  Serial.println(digital_sensor5);
}
void printSensor_Analog() {
  getSensor();
  Serial.print("Digital Sensor : ");
  Serial.print(analog_sensor1);
  Serial.print(" , ");
  Serial.print(analog_sensor2);
  Serial.print(" , ");
  Serial.print(analog_sensor3);
  Serial.print(" , ");
  Serial.print(analog_sensor4);
  Serial.print(" , ");
  Serial.println(analog_sensor5);
}

void getJoy() {
  swForward = digitalRead(pinJoy_Forward);
  swBackward = digitalRead(pinJoy_Backward);
  swLeft = digitalRead(pinJoy_Left);
  swRight = digitalRead(pinJoy_Right);
  swKeep = digitalRead(pinJoy_Keep);
  swLeave = digitalRead(pinJoy_Leave);
}
void printJoy() {
  getJoy();
  Serial.print("Joy Switch : ");
  Serial.print(swForward);
  Serial.print(" , ");
  Serial.print(swBackward);
  Serial.print(" , ");
  Serial.print(swLeft);
  Serial.print(" , ");
  Serial.print(swRight);
  Serial.print(" , ");
  Serial.print(swKeep);
  Serial.print(" , ");
  Serial.println(swLeave);
}
void setup_inputAutoBot() {

  pinMode(pinSensor1, INPUT);
  pinMode(pinSensor2, INPUT);
  pinMode(pinSensor3, INPUT);
  pinMode(pinSensor4, INPUT);
  pinMode(pinSensor5, INPUT);

  pinMode(pinSw1, INPUT_PULLUP);
  pinMode(pinSw2, INPUT_PULLUP);

  pinMode(pinJoy_Forward, INPUT_PULLUP);
  pinMode(pinJoy_Backward, INPUT_PULLUP);
  pinMode(pinJoy_Left, INPUT_PULLUP);
  pinMode(pinJoy_Right, INPUT_PULLUP);
  pinMode(pinJoy_Keep, INPUT_PULLUP);
  pinMode(pinJoy_Leave, INPUT_PULLUP);

}
void setup_inputManualBot() {

  pinMode(pinSw1, INPUT_PULLUP);
  pinMode(pinSw2, INPUT_PULLUP);

  pinMode(pinJoy_Forward, INPUT_PULLUP);
  pinMode(pinJoy_Backward, INPUT_PULLUP);
  pinMode(pinJoy_Left, INPUT_PULLUP);
  pinMode(pinJoy_Right, INPUT_PULLUP);
  pinMode(pinJoy_Keep, INPUT_PULLUP);
  pinMode(pinJoy_Leave, INPUT_PULLUP);
}
