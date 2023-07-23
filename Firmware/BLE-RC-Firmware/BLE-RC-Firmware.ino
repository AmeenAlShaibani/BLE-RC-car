#include <Arduino.h>
#include "BluetoothSerial.h"

const int M1_1  = 33;
const int M1_2  = 25;
const int M1_PWM  = 18;

const int M2_1  = 17;
const int M2_2  = 16;
const int M2_PWM  = 23;

const int M3_1  = 26;
const int M3_2  = 27;
const int M3_PWM  = 19;

const int M4_1  = 21;
const int M4_2  = 13;
const int M4_PWM  = 22;

const int STBY_M1M3  = 32;
const int STBY_M2M4  = 4;

BluetoothSerial SerialBT;

String device_name = "ESP32-BT-Slave";

void setup()

{
  //setup hm-10
  Serial.begin(115200);
  
  pinMode(M1_1,OUTPUT); 
  pinMode(M1_2,OUTPUT);
  pinMode(M1_PWM,OUTPUT);

  pinMode(M2_1,OUTPUT); 
  pinMode(M2_2,OUTPUT);
  pinMode(M2_PWM,OUTPUT);

  pinMode(M3_1,OUTPUT); 
  pinMode(M3_2,OUTPUT);
  pinMode(M3_PWM,OUTPUT);

  pinMode(M4_1,OUTPUT); 
  pinMode(M4_2,OUTPUT);
  pinMode(M4_PWM,OUTPUT);

  pinMode(STBY_M1M3,OUTPUT); 
  pinMode(STBY_M2M4,OUTPUT); 

  digitalWrite(STBY_M1M3,HIGH);
  digitalWrite(STBY_M2M4,HIGH);

  SerialBT.begin(device_name); //Bluetooth device name
  Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());

  delay(1000);
}

void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    char data = SerialBT.read();
    Serial.write(data);
    if(data == 'N') {
      north();
    } else if(data == 'E'){
      east();
    } else if(data == 'W'){
      west();
    } else if(data == 'S'){
      south();
    } else if(data == '0'){
      stop();
    }


  }
  delay(20);
}

void north() {
  runMotor1(1);
  runMotor2(1);
  runMotor3(1);
  runMotor4(1);
}

void south() {
  runMotor1(0);
  runMotor2(0);
  runMotor3(0);
  runMotor4(0);
}

void east() {
  runMotor1(0);
  runMotor2(1);
  runMotor3(0);
  runMotor4(1);
}

void west() {
  runMotor1(1);
  runMotor2(0);
  runMotor3(1);
  runMotor4(0);
}

void stop(){
  analogWrite(M1_PWM,0); //Speed control of Motor A
  analogWrite(M2_PWM,0); //Speed control of Motor A
  analogWrite(M3_PWM,0); //Speed control of Motor A
  analogWrite(M4_PWM,0); //Speed control of Motor A
}

void runMotor1(int dir){
  if (dir == 0) {
    digitalWrite(M1_1,HIGH); //Motor A Rotate Clockwise
    digitalWrite(M1_2,LOW);
  } else {
    digitalWrite(M1_1,LOW); //Motor A Rotate Clockwise
    digitalWrite(M1_2,HIGH);
  }
  analogWrite(M1_PWM,124); //Speed control of Motor A
}

void runMotor2(int dir){
  if (dir == 0) {
    digitalWrite(M2_1,HIGH); //Motor A Rotate Clockwise
    digitalWrite(M2_2,LOW);
  } else {
    digitalWrite(M2_1,LOW); //Motor A Rotate Clockwise
    digitalWrite(M2_2,HIGH);
  }
  analogWrite(M2_PWM,124); //Speed control of Motor A

}

void runMotor3(int dir){
  if (dir == 0) {
    digitalWrite(M3_1,LOW); //Motor A Rotate Clockwise
    digitalWrite(M3_2,HIGH);
  } else {
    digitalWrite(M3_1,HIGH); //Motor A Rotate Clockwise
    digitalWrite(M3_2,LOW);
  }
  analogWrite(M3_PWM,124); //Speed control of Motor A
}

void runMotor4(int dir){
  if (dir == 0) {
    digitalWrite(M4_1,HIGH); //Motor A Rotate Clockwise
    digitalWrite(M4_2,LOW);
  } else {
    digitalWrite(M4_1,LOW); //Motor A Rotate Clockwise
    digitalWrite(M4_2,HIGH);
  }

  analogWrite(M4_PWM,124); //Speed control of Motor A
}

//SINGLE MOTOR TEST

  // pinMode(M2_1,OUTPUT); 
  // pinMode(M2_2,OUTPUT);
  // pinMode(M2_PWM,OUTPUT);

  // pinMode(STBY_M1M3,OUTPUT); 
  // pinMode(STBY_M2M4,OUTPUT);

  // digitalWrite(M2_1,HIGH); //Motor A Rotate Clockwise
  // digitalWrite(M2_2,LOW);
  // digitalWrite(STBY_M1M3,LOW);
  // digitalWrite(STBY_M2M4,LOW);

  // analogWrite(M2_PWM,254); //Speed control of Motor A


  //This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial






