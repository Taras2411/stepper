#define STEP_ROUND 200 // количество шагов на 1 оборот
#define SPEED_MAX 1250
#define SPEED_MIN 0
#define ACCELERATION 0//30000
#define DIAMETER 68

#define PIN_STEP_1 3
#define PIN_DIR_1 2
#define PIN_EN_1 4

//#define PIN_STEP_1 11
//#define PIN_DIR_1 12
//#define PIN_EN_1 10


void setup() {
  Serial.begin(9600);
  pinMode(PIN_DIR_1, OUTPUT);
  pinMode(PIN_STEP_1, OUTPUT);
  pinMode(PIN_EN_1, OUTPUT);
  digitalWrite(PIN_DIR_1, HIGH);
  digitalWrite(PIN_EN_1, LOW);



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
}
int i = 0;
int speedInPerc = 0;

void loop() {

  delay(1000);
  speedInPerc += 10 ;
  Serial.print("SpeedIn%: ");
  Serial.print(speedInPerc);
  Serial.print(" i: ");
  Serial.print(i);
  Serial.print("over:  ");
  Serial.println((1.0 / (speedInPerc / 100.0))*10);
}



void motorFuncRight() {
  int over = (1.0 / (speedInPerc / 100.0))*10;
  if (i >= over) {

    digitalWrite(PIN_STEP_1, !digitalRead(PIN_STEP_1));
    i = 0;
  } else {
    i++;
  }
  
}




void motorFuncLeft() {
  //  digitalWrite(PIN_STEP_1, !digitalRead(PIN_STEP_1));
}

void ledSwitch() {
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}
