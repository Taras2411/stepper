
#include <Wire.h>                                     // подключаем библиотеку для работы с шиной I2C
#include <iarduino_I2C_connect.h>                     // подключаем библиотеку для соединения arduino по шине I2C
// Объявляем переменные и константы:
iarduino_I2C_connect I2C2;                            // объявляем переменную для работы c библиотекой iarduino_I2C_connect


void setup(){
//Wire.setClock(400000);                              // устанавливаем скорость передачи данных по шине I2C = 400кБит/с
  Wire.begin();                                   // инициируем подключение к шине I2C в качестве ведомого (slave) устройства, с указанием своего адреса на шине.
  Serial.begin(115200);
}

unsigned long stopMil = 0;
void loop(){
unsigned long startMil = millis();
int var = I2C2.readByte(0x01,0);
long hcsr04_arr[var];
hcsr04_arr[0] = I2C2.readByte(0x01,0);

hcsr04_arr[1]= I2C2.readByte(0x01,1)<<8;
hcsr04_arr[1]+= I2C2.readByte(0x01,2);

hcsr04_arr[2]= I2C2.readByte(0x01,3)<<8;
hcsr04_arr[2]+= I2C2.readByte(0x01,4);

hcsr04_arr[3]= I2C2.readByte(0x01,5)<<8;
hcsr04_arr[3]+= I2C2.readByte(0x01,6);

hcsr04_arr[4]= I2C2.readByte(0x01,7)<<8;
hcsr04_arr[4]+= I2C2.readByte(0x01,8);

String toOut = "Time of geting data by I2C = " + String(stopMil-startMil) + " Данные с датчика 1 = " + String(hcsr04_arr[1]) + " Данные с датчика 2 = " + String(hcsr04_arr[2])  + " Данные с датчика 3 = " + String(hcsr04_arr[3])  + " Данные с датчика 4 = " + String(hcsr04_arr[4]) ;
Serial.println(toOut);
stopMil = millis();

// Serial.print("Время опроса датчиков по шине = ");
// Serial.print((stopMil-startMil));
// Serial.print("Данные с датчика 1 = ");
// Serial.print(hcsr04_arr[1]);
// Serial.print("   Данные с датчика 2 = ");
// Serial.print(hcsr04_arr[2]);
// Serial.print("   Данные с датчика 3 = ");
// Serial.print(hcsr04_arr[3]);
// Serial.print("   Данные с датчика 4 = ");
// Serial.println(hcsr04_arr[4]);


}
