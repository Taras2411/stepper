/*  The range readings are in units of mm. */
#include <VL53L0X.h>
#define XSHUT1 3
#define XSHUT2 4
#define XSHUT3 5
#define XSHUT4 6

VL53L0X sensor1;
VL53L0X sensor2;
VL53L0X sensor3;
VL53L0X sensor4;


// Uncomment this line to use long range mode. This
// increases the sensitivity of the sensor and extends its
// potential range, but increases the likelihood of getting
// an inaccurate reading because of reflections from objects
// other than the intended target. It works best in dark
// conditions.

#define LONG_RANGE


// Uncomment ONE of these two lines to get
// - higher speed at the cost of lower accuracy OR
// - higher accuracy at the cost of lower speed

//#define HIGH_SPEED
//#define HIGH_ACCURACY


void setup()
{
  Wire.begin();
  sensor1.setTimeout(500);
  sensor2.setTimeout(500);
  sensor3.setTimeout(500);
  sensor4.setTimeout(500);

  pinMode(XSHUT1, OUTPUT);
  pinMode(XSHUT2, OUTPUT);
  pinMode(XSHUT3, OUTPUT);
  pinMode(XSHUT4, OUTPUT);

  digitalWrite(XSHUT1, LOW);
  digitalWrite(XSHUT2, LOW);
  digitalWrite(XSHUT3, LOW);
  digitalWrite(XSHUT4, LOW);
  delay(10);

  digitalWrite(XSHUT1, HIGH);
  digitalWrite(XSHUT2, LOW);
  digitalWrite(XSHUT3, LOW);
  digitalWrite(XSHUT4, LOW);
  boolean sensor1_initResult = sensor1.init();
  sensor1.setAddress(0x31);

  digitalWrite(XSHUT1, HIGH);
  digitalWrite(XSHUT2, HIGH);
  digitalWrite(XSHUT3, LOW);
  digitalWrite(XSHUT4, LOW);
  boolean sensor2_initResult = sensor2.init();
  sensor2.setAddress(0x32);

  digitalWrite(XSHUT1, HIGH);
  digitalWrite(XSHUT2, HIGH);
  digitalWrite(XSHUT3, HIGH);
  digitalWrite(XSHUT4, LOW);
  boolean sensor3_initResult = sensor3.init();
  sensor3.setAddress(0x33);

  digitalWrite(XSHUT1, HIGH);
  digitalWrite(XSHUT2, HIGH);
  digitalWrite(XSHUT3, HIGH);
  digitalWrite(XSHUT4, HIGH);
  boolean sensor4_initResult = sensor4.init();
  sensor4.setAddress(0x34);

  Serial.begin(9600);

  if (!sensor1_initResult)Serial.println(F("Failed to detect and initialize sensor №1 !"));
  if (!sensor2_initResult)Serial.println(F("Failed to detect and initialize sensor №2 !"));
  if (!sensor3_initResult)Serial.println(F("Failed to detect and initialize sensor №3 !"));
  if (!sensor4_initResult)Serial.println(F("Failed to detect and initialize sensor №4 !"));

#if defined LONG_RANGE
  // lower the return signal rate limit (default is 0.25 MCPS)
  sensor1.setSignalRateLimit(0.1);
  sensor2.setSignalRateLimit(0.1);
  sensor3.setSignalRateLimit(0.1);
  sensor4.setSignalRateLimit(0.1);
  // increase laser pulse periods (defaults are 14 and 10 PCLKs)
  sensor1.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
  sensor1.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);
  sensor2.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
  sensor2.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);
  sensor3.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
  sensor3.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);
  sensor4.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
  sensor4.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);
#endif

#if defined HIGH_SPEED
  // reduce timing budget to 20 ms (default is about 33 ms)
  sensor1.setMeasurementTimingBudget(20000);
  sensor2.setMeasurementTimingBudget(20000);
  sensor3.setMeasurementTimingBudget(20000);
  sensor4.setMeasurementTimingBudget(20000);
#elif defined HIGH_ACCURACY
  // increase timing budget to 200 ms
  sensor1.setMeasurementTimingBudget(200000);
  sensor2.setMeasurementTimingBudget(200000);
  sensor3.setMeasurementTimingBudget(200000);
  sensor4.setMeasurementTimingBudget(200000);
#endif
}

void loop()
{
  Serial.println(F("Measured distance:"));
  Serial.print(F("Sensor1: "));
  Serial.print(sensor1.readRangeSingleMillimeters());
  if (sensor1.timeoutOccurred()) {
    Serial.print(F(" TIMEOUT"));
  }
  Serial.println();
  Serial.print(F("Sensor2: "));
  Serial.print(sensor2.readRangeSingleMillimeters());
  if (sensor2.timeoutOccurred()) {
    Serial.print(F(" TIMEOUT"));
  }
  Serial.println();
  Serial.print(F("Sensor3: "));
  Serial.print(sensor3.readRangeSingleMillimeters());
  if (sensor3.timeoutOccurred()) {
    Serial.print(F(" TIMEOUT"));
  }
  Serial.println();
  Serial.print(F("Sensor4: "));
  Serial.print(sensor4.readRangeSingleMillimeters());
  if (sensor4.timeoutOccurred()) {
    Serial.print(F(" TIMEOUT"));
  }
  Serial.println();
  Serial.println();
}
