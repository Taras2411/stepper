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
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

#include <Wire.h>
#include <iarduino_I2C_connect.h>   
#include <NewPing.h> 
NewPing sonar1(TRIG, ECHO, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar2(TRIG2, ECHO2, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar3(TRIG3, ECHO3, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar4(TRIG4, ECHO4, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
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
  int hcsr04_1 = sonar1.ping_cm();
  int hcsr04_2 = sonar2.ping_cm();
  int hcsr04_3 = sonar3.ping_cm();
  int hcsr04_4 = sonar4.ping_cm();
  long stopMil = micros();
  Serial.print("Время опроса датчиков не по шине = ");
  Serial.println((stopMil-startMil));
/*
Serial.print("Данные с датчика 1 ПРЯМИКОМ С ДАТЧИКА! = ");
Serial.print(hcsr04_1);
Serial.print("   Данные с датчика 2 = ");
Serial.print(hcsr04_2);
Serial.print("   Данные с датчика 3 = ");
Serial.print(hcsr04_3);
Serial.print("   Данные с датчика 4 = ");
Serial.println(hcsr04_4);
*/
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