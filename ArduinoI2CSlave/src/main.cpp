#include <Arduino.h>
//Slave
// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

// Created 29 March 2006

// This example code is in the public domain.
#define TRIG 2
#define ECHO 3
#define TRIG2 4
#define ECHO2 5
#define TRIG3 6
#define ECHO3 7
#define TRIG4 8
#define ECHO4 9


#include <Wire.h>
#include <iarduino_I2C_connect.h>   
#include <iarduino_HC_SR04.h>    
iarduino_HC_SR04 hcsr1(TRIG, ECHO);
iarduino_HC_SR04 hcsr2(TRIG2, ECHO2);
iarduino_HC_SR04 hcsr3(TRIG3, ECHO3);
iarduino_HC_SR04 hcsr4(TRIG4, ECHO4);
byte REG_Array[9];
iarduino_I2C_connect I2C2;   
void setup()
{
  Wire.begin(0x01); // join i2c bus (address optional for master)
  I2C2.begin(REG_Array);       
  Serial.begin(9600);
}



void loop()
{
  long startMil = micros();
  int hcsr04_1 = hcsr1.distance();
  int hcsr04_2 = hcsr2.distance();
  int hcsr04_3 = hcsr3.distance();
  int hcsr04_4 = hcsr4.distance();
  long stopMil = micros();
  Serial.print("Время опроса датчиков не по шине = ");
  Serial.println((stopMil-startMil));

/*Serial.print("Данные с датчика 1 ПРЯМИКОМ С ДАТЧИКА! = ");
Serial.print(hcsr04_1);
Serial.print("   Данные с датчика 2 = ");
Serial.print(hcsr04_2);
Serial.print("   Данные с датчика 3 = ");
Serial.print(hcsr04_3);
Serial.print("   Данные с датчика 4 = ");
Serial.println(hcsr04_4);*/
  REG_Array[0] = 9;

  REG_Array[1] = hcsr04_1>>8;
  REG_Array[2] = hcsr04_1;

  REG_Array[3] = hcsr04_2>>8;
  REG_Array[4] = hcsr04_2;
  
  REG_Array[5] = hcsr04_3>>8;
  REG_Array[6] = hcsr04_3;
  
  REG_Array[7] = hcsr04_4>>8;
  REG_Array[8] = hcsr04_4;



}