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
  Serial.begin(9600);
  pinMode(PIN_DIR_1, OUTPUT);
  pinMode(PIN_STEP_1, OUTPUT);
  pinMode(PIN_EN_1, OUTPUT);
  digitalWrite(PIN_DIR_1, HIGH);
  digitalWrite(PIN_EN_1, LOW);

  pinMode(PIN_DIR_2, OUTPUT);
  pinMode(PIN_STEP_2, OUTPUT);
  pinMode(PIN_EN_2, OUTPUT);
  digitalWrite(PIN_DIR_2, LOW);
  digitalWrite(PIN_EN_2, LOW);

  TCCR1A = 0;
  TCCR1B = 0;
  OCR1A = 3276;//32768
  bitSet(TCCR1B, CS10);  // 256 prescaler
  bitSet(TCCR1B, WGM12);
  bitSet(TIMSK1, OCIE1A); // timer overflow interrupt
  pinMode(LED_BUILTIN, OUTPUT);



}

ISR(TIMER1_COMPA_vect) {
  ledSwitch();
  motorFuncRight();
  motorFuncLeft();
}


int iRight = 0;
int speedInPercRight = 0;

int iLeft = 0;
int speedInPercLeft = 0;

void loop() {
  //ОТЛАДКА
  delay(5000);
  speedInPercRight -= 10 ;
  speedInPercLeft -= 10 ;
  Serial.print("SpeedIn%: ");
  Serial.print(speedInPercRight);
  Serial.print(" iRight: ");
  Serial.print(iRight);
  Serial.print("over:  ");
  Serial.println((1.0 / (speedInPercRight / 100.0)) * 10);
  //\ОТЛАДКА
}



void motorFuncRight() {
  if (speedInPercRight > 0) {
    digitalWrite(PIN_DIR_1, HIGH);
  }

  if (speedInPercRight < 0) {
    digitalWrite(PIN_DIR_1, LOW);
  }

  if (speedInPercRight != 0) {
    int over = (1.0 / (abs(speedInPercRight) / 100.0)) * 10;
    if (iRight >= over) {


      digitalWrite(PIN_STEP_1, !digitalRead(PIN_STEP_1));
      iRight = 0;
    } else {
      iRight++;
    }
  } else {
    digitalWrite(PIN_STEP_1, LOW);
  }
}





void motorFuncLeft() {
  if (speedInPercLeft > 0) {
    digitalWrite(PIN_DIR_2, LOW);
  }

  if (speedInPercLeft < 0) {
    digitalWrite(PIN_DIR_2, HIGH);
  }

  if (speedInPercLeft != 0) {
    int over = (1.0 / (abs(speedInPercLeft) / 100.0)) * 10;
    if (iLeft >= over ) {
      digitalWrite(PIN_STEP_2, !digitalRead(PIN_STEP_2));
      iLeft = 0;
    } else {
      iLeft++;
    }
  } else {
    digitalWrite(PIN_STEP_2, LOW);
  }
}

void ledSwitch() {
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}
