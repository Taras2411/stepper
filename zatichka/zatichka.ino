#define STEP_ROUND 200 // количество шагов на 1 оборот
#define SPEED_MAX 1250
#define SPEED_MIN 0
#define ACCELERATION 0//30000
#define DIAMETER 68

#define PIN_STEP_1 3
#define PIN_DIR_1 2
#define PIN_EN_1 4

#define PIN_STEP_2 11
#define PIN_DIR_2 12
#define PIN_EN_2 10



void setup() {
  // put your setup code here, to run once:
pinMode(PIN_EN_1,OUTPUT);
pinMode(PIN_EN_2,OUTPUT);


digitalWrite(PIN_EN_1, HIGH);
digitalWrite(PIN_EN_2, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:

}
