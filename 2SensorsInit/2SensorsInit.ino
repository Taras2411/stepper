#include "Adafruit_VL53L0X.h"
#include <Wire.h>
#define XSHUT1 5
#define XSHUT2 6
#define XSHUT3 7


Adafruit_VL53L0X lox = Adafruit_VL53L0X();
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();
//Adafruit_VL53L0X lox3 = Adafruit_VL53L0X();
//Adafruit_VL53L0X lox4 = Adafruit_VL53L0X();

bool lox1Out;
bool lox2Out;
void setup() {
  // put your setup code here, to run once:
  Wire.begin();

  pinMode(XSHUT1, OUTPUT);
  pinMode(XSHUT2, OUTPUT);
  pinMode(XSHUT3, OUTPUT);


  digitalWrite(XSHUT1, LOW);
  digitalWrite(XSHUT2, LOW);
  digitalWrite(XSHUT3, LOW);
  delay(100);

  digitalWrite(XSHUT1, LOW);
  digitalWrite(XSHUT2, HIGH);
  digitalWrite(XSHUT3, LOW);
  delay(100);
  lox1Out = lox.begin(0x30);
  delay(100);
  digitalWrite(XSHUT1, HIGH);
//  digitalWrite(XSHUT2, HIGH);
  digitalWrite(XSHUT3, LOW);
  delay(100);
  lox2Out = lox2.begin(0x31);
  delay(100);
  digitalWrite(XSHUT1, HIGH);
  digitalWrite(XSHUT2, HIGH);
  digitalWrite(XSHUT3, LOW);
//      digitalWrite(XSHUT1,LOW);
//      digitalWrite(XSHUT2,LOW);
  //  digitalWrite(XSHUT3,HIGH);
  //  digitalWrite(XSHUT4,LOW);
  //  lox3.begin(0x32);
  //
  //  digitalWrite(XSHUT1,LOW);
  //  digitalWrite(XSHUT2,LOW);
  //  digitalWrite(XSHUT3,LOW);
  //  digitalWrite(XSHUT4,HIGH);
  //  lox4.begin(0x33);

  Serial.begin(9600);
  Serial.println("init complit");


}

void loop() {
  byte error, address;
  int nDevices;
Serial.println(lox1Out);
Serial.println(lox2Out);
  Serial.println("Scanning...");

  nDevices = 0;
  for (address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error == 4)
    {
      Serial.print("Unknown error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

  delay(5000);           // wait 5 seconds for next scan

  // put your main code here, to run repeatedly:

}
