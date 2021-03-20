#include <NewPing.h>

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


#define MAX_DISTANCE 200

NewPing front(FRONT_TRIG, FRONT_ECHO, MAX_DISTANCE);
NewPing left(LEFT_TRIG, LEFT_ECHO, MAX_DISTANCE);
NewPing right(RIGHT_TRIG, RIGHT_ECHO, MAX_DISTANCE);
NewPing back(BACK_TRIG, BACK_ECHO, MAX_DISTANCE);



void setup() {
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


  digitalWrite(FRONT_GND, LOW);
  digitalWrite(FRONT_VCC, HIGH);
  digitalWrite(LEFT_GND, LOW);
  digitalWrite(LEFT_VCC, HIGH);
  digitalWrite(RIGHT_GND, LOW);
  digitalWrite(RIGHT_VCC, HIGH);
  digitalWrite(BACK_GND, LOW);
  digitalWrite(BACK_VCC, HIGH);

}

void loop() {
  Serial.print("FRONT: ");
  Serial.print(front.ping_cm());
  Serial.print("  LEFT: ");
  Serial.print(left.ping_cm());
  Serial.print("  RIGHT: ");
  Serial.print(right.ping_cm());
  Serial.print("  BACK: ");
  Serial.println(back.ping_cm());

  // put your main code here, to run repeatedly:

}
