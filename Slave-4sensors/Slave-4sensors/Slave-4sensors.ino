#include <Wire.h>

// left = 0
//right = 1
//back = 2
//front = 3



#include <iarduino_I2C_connect.h>

#define FRONT_VCC 16
#define FRONT_GND 18
#define FRONT_ECHO 12
#define FRONT_TRIG 14

#define LEFT_VCC 27
#define LEFT_GND 29
#define LEFT_ECHO 23
#define LEFT_TRIG 25

#define RIGHT_VCC 37
#define RIGHT_GND 35
#define RIGHT_ECHO 41
#define RIGHT_TRIG 39

#define BACK_VCC 38
#define BACK_GND 36
#define BACK_ECHO 42
#define BACK_TRIG 40


#define MAX_DIST 150
#define MAX_DUR MAX_DIST * 58 //165

#define filter 10

int RAW_ARR[4][filter];
int FILT_ARR[4];

byte REG_Array[9];
iarduino_I2C_connect I2C2;

void setup() {
  Wire.begin(0x01); // join i2c bus (address optional for master)
  I2C2.begin(REG_Array);
  Serial.begin(115200);
  // put your setup code here, to run once:
  pinMode(FRONT_VCC, OUTPUT);
  pinMode(FRONT_GND, OUTPUT);
  pinMode(LEFT_VCC, OUTPUT);
  pinMode(LEFT_GND, OUTPUT);
  pinMode(RIGHT_VCC, OUTPUT);
  pinMode(RIGHT_GND, OUTPUT);
  pinMode(BACK_VCC, OUTPUT);
  pinMode(BACK_GND, OUTPUT);





  pinMode(FRONT_TRIG, OUTPUT);
  pinMode(FRONT_ECHO, INPUT);
  pinMode(LEFT_TRIG, OUTPUT);
  pinMode(LEFT_ECHO, INPUT);
  pinMode(RIGHT_TRIG, OUTPUT);
  pinMode(RIGHT_ECHO, INPUT);
  pinMode(BACK_TRIG, OUTPUT);
  pinMode(BACK_ECHO, INPUT);

  Serial.print("Lets start ");

  digitalWrite(FRONT_GND, LOW);
  digitalWrite(FRONT_VCC, HIGH);
  digitalWrite(LEFT_GND, LOW);
  digitalWrite(LEFT_VCC, HIGH);
  digitalWrite(RIGHT_GND, LOW);
  digitalWrite(RIGHT_VCC, HIGH);
  digitalWrite(BACK_GND, LOW);
  digitalWrite(BACK_VCC, HIGH);
  delay(1000);
  for (int i; i < filter ; i++) {
    int tmp = int(HcSr04Ping("left"));
    RAW_ARR[0][i] = tmp;
  }
  for (int i; i < filter ; i++) {
    int tmp = int(HcSr04Ping("right"));

    RAW_ARR[1][i] = tmp;
  }
  for (int i; i < filter ; i++) {
    int tmp = int(HcSr04Ping("back"));

    RAW_ARR[2][i] = tmp;
  }
  for (int i; i < filter ; i++) {
    int tmp = int(HcSr04Ping("front"));


    RAW_ARR[3][i] = tmp;
  }




  for (int y = 0; y < 4; y++) {

    for (int x = 0; x < filter; x++) {


    }
  
  }




}


void loop() {
  //  delay(1000);
  Serial.println("IM IN LOOP!");
  Serial.println("LOOP LEFT START!");
  //left
  for (int i = filter - 1; i != 0 ; i--) {
    RAW_ARR[0][i] = RAW_ARR[0][i - 1];
  }
  RAW_ARR[0][0] = int(HcSr04Ping("left"));


  //right

  for (int i = filter - 1; i != 0 ; i--) {
    RAW_ARR[1][i] = RAW_ARR[1][i - 1];
  }
  RAW_ARR[1][0] = int(HcSr04Ping("right"));

  //back

  for (int i = filter - 1; i != 0 ; i--) {
    RAW_ARR[2][i] = RAW_ARR[2][i - 1];
  }
  RAW_ARR[2][0] = int(HcSr04Ping("back"));

 
  //front

  for (int i = filter - 1; i != 0 ; i--) {
    RAW_ARR[3][i] = RAW_ARR[3][i - 1];
  }
  RAW_ARR[3][0] = int(HcSr04Ping("front"));


  for (int y = 0; y < 4; y++) {

    for (int x = 0; x < filter; x++) {
   
    }

  }




  for (int y = 0; y < 4; y++) {
    float temp = 0;
    for (int x = 0; x < filter; x++) {
      temp += RAW_ARR[y][x];

    }
    temp = temp / filter;
    FILT_ARR[y] = temp;
  }



  for (int y = 0; y < 4; y++) {


  }




  REG_Array[0] = 9;

  REG_Array[1] = FILT_ARR[0] >> 8;
  REG_Array[2] = FILT_ARR[0];

  REG_Array[3] = FILT_ARR[1] >> 8;
  REG_Array[4] = FILT_ARR[1];

  REG_Array[5] = FILT_ARR[2] >> 8;
  REG_Array[6] = FILT_ARR[2];

  REG_Array[7] = FILT_ARR[3] >> 8;
  REG_Array[8] = FILT_ARR[3];
}

float HcSr04Ping(String directionOfSensor)
{
  if (directionOfSensor == "left")
  {

    int duration, distance1;
    digitalWrite(LEFT_TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(LEFT_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(LEFT_TRIG, LOW);
    duration = pulseIn(LEFT_ECHO, HIGH, MAX_DUR);
    distance1 = duration / 58;
    //    return 42;
    return distance1;
  }



  if (directionOfSensor == "right")
  {

    int duration, distance1;
    digitalWrite(RIGHT_TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(RIGHT_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(RIGHT_TRIG, LOW);
    duration = pulseIn(RIGHT_ECHO, HIGH, MAX_DUR);
    distance1 = duration / 58;
    // return 42;
    return distance1;
  }


  if (directionOfSensor == "back")
  {

    int duration, distance1;
    digitalWrite(BACK_TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(BACK_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(BACK_TRIG, LOW);
    duration = pulseIn(BACK_ECHO, HIGH, MAX_DUR);
    distance1 = duration / 58;
    //    return 42;
    return distance1;
  }

  if (directionOfSensor == "front")
  {

    int duration, distance1;
    digitalWrite(FRONT_TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(FRONT_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(FRONT_TRIG, LOW);
    duration = pulseIn(FRONT_ECHO, HIGH, MAX_DUR);
    distance1 = duration / 58;
    //    return 42;
    return distance1;
  }


}
