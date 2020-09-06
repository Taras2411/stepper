



#define SPEED_MAX 1250 //максимальная отробатываемае скорость моторов
#define STEP_ROUND 200 // количество шагов на 1 оборот


#define PIN_STEP_1 3
#define PIN_DIR_1 2
#define PIN_STEP_2 5
#define PIN_DIR_2 4



void setup() {

  // режим для STEP и DIR как OUTPUT

  pinMode(PIN_STEP_1, OUTPUT);
  pinMode(PIN_DIR_1, OUTPUT);
  pinMode(PIN_STEP_2, OUTPUT);
  pinMode(PIN_DIR_2, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(PIN_DIR_1, HIGH);
  digitalWrite(PIN_DIR_2, HIGH);
  // начальные значения


}

void loop() {
  delay(2000);
  /*for (int i = 0; i < 200; i++) {
    digitalWrite(PIN_STEP_1, HIGH);
    digitalWrite(PIN_STEP_2, HIGH);
    digitalWrite(13, HIGH);
    delayMicroseconds(400);
    digitalWrite(PIN_STEP_1, LOW);
    digitalWrite(PIN_STEP_2, LOW);
    digitalWrite(13, LOW);
    delayMicroseconds(400);
    }
    //goStepsL(1,90,500);
    //goStepsR(1,90,500);
  */
  motor_speed_on(100, 100);
}
void motor_speed_on(float spL, float spR) {
  if (spL >= 0) {
    while (1 == 1) {
      digitalWrite(PIN_DIR_1, HIGH);
      digitalWrite(PIN_STEP_1, HIGH);
      //digitalWrite(13, HIGH);
      delayMicroseconds(100 / spL * 400);
      digitalWrite(PIN_STEP_1, LOW);
    
      //digitalWrite(13, LOW);
      delayMicroseconds(100 / spL * 400);
    }
  } else {
    digitalWrite(PIN_DIR_1, LOW);
    digitalWrite(PIN_STEP_1, HIGH);
    //digitalWrite(13, HIGH);
    delayMicroseconds(100 / spL * 400);
    digitalWrite(PIN_STEP_1, LOW);
    //digitalWrite(13, LOW);
    delayMicroseconds(100 / spL * 400);
  }
}
