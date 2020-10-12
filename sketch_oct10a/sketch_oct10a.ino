#define PIN_STEP_1 8
#define PIN_DIR_1 10
#define PIN_STEP_2 31
#define PIN_DIR_2 26
#define PIN_EN_2 30
#define PIN_EN_1 9


void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_EN_1, OUTPUT);
  pinMode(PIN_STEP_1, OUTPUT);
  pinMode(PIN_DIR_1, OUTPUT);

  digitalWrite(PIN_DIR_1, HIGH);
  digitalWrite(PIN_EN_1, LOW);

  pinMode(PIN_EN_2, OUTPUT);
  pinMode(PIN_STEP_2, OUTPUT);
  pinMode(PIN_DIR_2, OUTPUT);

  digitalWrite(PIN_DIR_2, HIGH);
  digitalWrite(PIN_EN_2, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
    digitalWrite(PIN_STEP_1, HIGH);
    digitalWrite(PIN_STEP_2, HIGH);
    delay(2);
    digitalWrite(PIN_STEP_1, LOW);
    digitalWrite(PIN_STEP_2, LOW);
    delay(2);
  
}
