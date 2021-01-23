#include "iarduino_HC_SR04.h"
//		инициализация модуля
		iarduino_HC_SR04::iarduino_HC_SR04(uint8_t i, uint8_t j){	//	i: № вывода TRIG, j: № вывода ECHO)
		pinTRIG=i; pinMode(pinTRIG, OUTPUT);						//	Сохраняем № вывода TRIG и устанавливаем ему режим работы на выход
		pinECHO=j; pinMode(pinECHO, INPUT );						//	Сохраняем № вывода ECHO и устанавливаем ему режим работы на вход
		digitalWrite(pinTRIG, LOW);									//	Устанавливаем уровень логического «0» на выводе TRIG
}
//		определение расстояния
long	iarduino_HC_SR04::distance(int8_t i){						//	i: текущая температура в °C
		long		j=funDuration();								//	Считываем длительность импульса на выводе ECHO
		if(j<400){	j=funDuration();}								//	Повторно считываем длительность импульса (для подавления "глюков" некоторых датчиков)
					j=j*sqrt(273+i)/1000;							//	Определяем расстояние: L = Echo * корень(t+273) / 1000
		if(j>400){	j=400;}											//	Ограничиваемся максимально допустимым расстоянием
		if(averaging<=0){valDATA=float(j);}else{					//	Если усреднение результата не требуется, то текущий результат и есть выводимый результат, иначе ...
			valDATA *= float(averaging);							//	Умножаем предыдущий результат на коэффициент усреднения - 1
			valDATA += j;											//	Добавляем к полученному значению текущий результат
			valDATA /= float(averaging)+1.0;						//	Делим полученное значение на коэффициент усреднения
		}															//
		return long(valDATA);										//	Выводим результат
}
//		определение длительности
long	iarduino_HC_SR04::funDuration(){
		digitalWrite(pinTRIG, HIGH);								//	Устанавливаем уровень логической «1» на выводе TRIG
		delayMicroseconds(10);										//	Ждём 10 мкс
		digitalWrite(pinTRIG, LOW);									//	Устанавливаем уровень логического «0» на выводе TRIG
		return pulseIn(pinECHO, HIGH);								//	Считываем длительность импульса на выводе ECHO
}
