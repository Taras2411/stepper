// пример с тиком по прерыванию таймера
// используется GyverTimers

#include <GyverStepper.h>
#define STEP_ROUND 200 // количество шагов на 1 оборот
#define SPEED_MAX 1250

#define PIN_STEP_1 3
#define PIN_DIR_1 2
#define PIN_STEP_2 5
#define PIN_DIR_2 4

#define ANGLE 3

GStepper< STEPPER2WIRE> stepper1(STEP_ROUND, PIN_STEP_1, PIN_DIR_1);
GStepper< STEPPER2WIRE> stepper2(STEP_ROUND, PIN_STEP_2, PIN_DIR_2);
// мотор с драйвером ULN2003 подключается по порядку пинов, но крайние нужно поменять местами
// то есть у меня подключено D2-IN1, D3-IN2, D4-IN3, D5-IN4, но в программе поменял 5 и 2

#include <GyverTimers.h>

void setup() {
  Serial.begin(115200);

  stepper1.setRunMode(FOLLOW_POS);
  stepper1.setMaxSpeed(1000);
  stepper1.setAcceleration(300);


  // мотор 2 будет делать sweep по проверке tick
  stepper2.setRunMode(FOLLOW_POS);
  stepper2.setMaxSpeed(1000);
  stepper2.setAcceleration(300);

  // настраиваем прерывания с периодом, при котором
  // система сможет обеспечить максимальную скорость мотора.
  // Для большей плавности лучше лучше взять период чуть меньше, например в два раза
  Timer2.setPeriod(stepper1.getMinPeriod() / 2);
  Timer2.setPeriod(stepper2.getMinPeriod() / 2);

  // взводим прерывание
  Timer2.enableISR();
  delay(1000);
  moveTank(50, 00, ANGLE, 360);

}

// обработчик
ISR(TIMER2_A) {
  stepper1.tick(); // тикаем тут
  stepper2.tick(); // тикаем тут
}

void loop() {
//  moveTank(50, 50, ANGLE, 360);
  
}

void moveTank(float spL, float spR, int mode, float value) {
  switch (mode) {
    case ANGLE:s
      stepper1.setRunMode(FOLLOW_POS);
      stepper2.setRunMode(FOLLOW_POS);
      if (map(spL, -100, 100, SPEED_MAX * 1, SPEED_MAX ) >= 0) {
        stepper1.setMaxSpeed(map(spL, -100, 100, SPEED_MAX * 1, SPEED_MAX));
        stepper1.setTargetDeg(value,RELATIVE);
      }
      if (map(spL, -100, 100, SPEED_MAX * 1, SPEED_MAX) < 0) {
        stepper1.setMaxSpeed(map(spL, -100, 100, SPEED_MAX * 1, SPEED_MAX));
        stepper1.setTargetDeg(value * -1,RELATIVE);
      }
      if (map(spR, -100, 100, SPEED_MAX * 1, SPEED_MAX) >= 0) {
        stepper2.setMaxSpeed(map(spL, -100, 100, SPEED_MAX * 1, SPEED_MAX));
        stepper2.setTargetDeg(value,RELATIVE);
      }
      if (map(spR, -100, 100, SPEED_MAX * 1, SPEED_MAX) < 0) {
        stepper2.setMaxSpeed(map(spL, -100, 100, SPEED_MAX * 1, SPEED_MAX));
        stepper2.setTargetDeg(value * -1,RELATIVE);
      }
      break;
  }
}
