// пример с тиком по прерыванию таймера
// используется GyverTimers

#include <GyverStepper.h>
#define STEP_ROUND 200 // количество шагов на 1 оборот
#define SPEED_MAX 1250
#define SPEED_MIN 0
#define ACCELERATION 30000

#define PIN_STEP_1 3
#define PIN_DIR_1 2
#define PIN_STEP_2 5
#define PIN_DIR_2 4

#define PIN_EN_2 44
#define PIN_EN_1 46


#define ANGLE 3

GStepper< STEPPER2WIRE> stepper1(STEP_ROUND, PIN_STEP_1, PIN_DIR_1, PIN_EN_1);
GStepper< STEPPER2WIRE> stepper2(STEP_ROUND, PIN_STEP_2, PIN_DIR_2, PIN_EN_2);
// мотор с драйвером ULN2003 подключается по порядку пинов, но крайние нужно поменять местами
// то есть у меня подключено D2-IN1, D3-IN2, D4-IN3, D5-IN4, но в программе поменял 5 и 2

#include <GyverTimers.h>

void setup() {
  pinMode(PIN_EN_1, OUTPUT);
  pinMode(PIN_EN_2, OUTPUT);
  digitalWrite(PIN_EN_1, HIGH);
  digitalWrite(PIN_EN_2, HIGH);
  Serial.begin(115200);

  stepper1.setRunMode(FOLLOW_POS);
  stepper1.setMaxSpeed(1000);
  stepper1.setAcceleration(0);


  // мотор 2 будет делать sweep по проверке tick
  stepper2.setRunMode(FOLLOW_POS);
  stepper2.setMaxSpeed(1000);
  stepper2.setAcceleration(0);

  // настраиваем прерывания с периодом, при котором
  // система сможет обеспечить максимальную скорость мотора.
  // Для большей плавности лучше лучше взять период чуть меньше, например в два раза
  Timer2.setPeriod(stepper1.getMinPeriod() / 2);
  Timer2.setPeriod(stepper2.getMinPeriod() / 2);

  // взводим прерывание
  Timer2.enableISR();
  delay(1000);
  //  moveTank(50, 00, ANGLE, 360);

}

// обработчик
ISR(TIMER2_A) {
  stepper1.tick(); // тикаем тут
  stepper2.tick(); // тикаем тут
}

void loop() {
  moveTank(10, 10, ANGLE, 360);
  //    Serial.println("I finished!!");
  //  stepper1.setMaxSpeed(abs(0));
  //  stepper1.setTargetDeg(360,RELATIVE);
  delay(100);
}

void moveTank(float spL, float spR, int mode, float value) {
  switch (mode) {
    case ANGLE:

      int spL_int = map(spL, -100, 100, SPEED_MAX * -1, SPEED_MAX);
      int spR_int = map(spR, -100, 100, SPEED_MAX * -1, SPEED_MAX);
      if (spL == 0) {
        stepper1.setAcceleration(0);
      }else{
        stepper1.setAcceleration(ACCELERATION);
      }
      if (spR == 0) {
        stepper2.setAcceleration(0);
      }else{
        stepper2.setAcceleration(ACCELERATION);
      }
      Serial.println("spl= ");
      Serial.print(spL_int);
      Serial.println("spr= ");
      Serial.print(spR_int);
      stepper1.setMaxSpeed(abs(0));
      stepper2.setMaxSpeed(abs(0));
      stepper1.setRunMode(FOLLOW_POS);
      stepper2.setRunMode(FOLLOW_POS);
      if (spL_int >= 0) {
        Serial.println("spl>=0 ");
        stepper1.setTargetDeg(value, RELATIVE);
      }
      if (spL_int < 0) {
        Serial.println("spl<0 ");
        stepper1.setTargetDeg(value * -1, RELATIVE);
      }
      if (spR_int >= 0) {
        Serial.println("spR>=0 ");
        stepper2.setTargetDeg(value, RELATIVE);
      }
      if (spR_int < 0) {
        Serial.println("spR<0 ");
        stepper2.setTargetDeg(value * -1, RELATIVE);
      }
      while (stepper1.tick() == true || stepper2.tick() == true) {
        delay(1);
        Serial.println("Speed:");
        Serial.print(stepper1.getSpeed());
        //        Serial.println("CurrentDeg:");
        //        Serial.print(stepper1.getCurrentDeg());
      }
      break;
  }
}
