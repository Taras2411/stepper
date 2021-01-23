[![](https://iarduino.ru/img/logo.svg)](https://iarduino.ru)[![](https://wiki.iarduino.ru/img/git-shop.svg?3)](https://iarduino.ru) [![](https://wiki.iarduino.ru/img/git-wiki.svg?2)](https://wiki.iarduino.ru) [![](https://wiki.iarduino.ru/img/git-lesson.svg?2)](https://lesson.iarduino.ru)[![](https://wiki.iarduino.ru/img/git-forum.svg?2)](http://forum.trema.ru)

# iarduino\_HC\_SR04

**This is a library for Arduino IDE. It allows to work with [Ultrasound distance sensor HC-SR04](https://iarduino.ru/shop/Sensory-Datchiki/ultrazvukovogo-datchika-hc-sr04-rasstoyaniya-dvizheniya.html) module**

**Данная библиотека для Arduino IDE позволяет работать с модулем [Ультразвуковой датчик HC-SR04](https://iarduino.ru/shop/Sensory-Datchiki/ultrazvukovogo-datchika-hc-sr04-rasstoyaniya-dvizheniya.html)**

> Подробнее про установку библиотеки читайте в нашей [инструкции](https://wiki.iarduino.ru/page/Installing_libraries/).

> Подробнее про подключение к [Arduino UNO](https://iarduino.ru/shop/boards/arduino-uno-r3.html)/[Piranha UNO](https://iarduino.ru/shop/boards/piranha-uno-r3.html) читайте на нашей [wiki](https://wiki.iarduino.ru/page/ultrazvukovoy-datchik-izmereniya-rasstoyaniya-hc-sr04/#h3_3)


| Модель | Ссылка на магазин |
|---|---|
| <p>Ультразвуковой датчик расстояния HC-SR04</p> <img src="https://wiki.iarduino.ru/img/resources/70/70.svg" width="150px"></img>| https://iarduino.ru/shop/Sensory-Datchiki/ultrazvukovogo-datchika-hc-sr04-rasstoyaniya-dvizheniya.html |


Данная библиотека отправляет стартовый сигнал датчику, ждёт сигнал ответа и преобразует длительность сигнала ответа в расстояние. Выполнение кода скетча приостанавливается на время ожидания сигнала ответа от датчика, которое может достигать 38 мс. Если Ваш код критичен к таким задержкам, воспользуйтесь библиотекой использующей внешнее прерывание [iarduino\_HC\_SR04\_int.h](https://github.com/tremaru/iarduino_HC_SR04_int), которая не ждёт ответа от датчика, а сразу возвращает расстояние прочитанное при предыдущем запросе. Синтаксис обеих библиотек одинаков.


## Назначение функций:

**Подробное описание работы с библиотекой и примеры смотрите на [нашем сайте](https://wiki.iarduino.ru/page/ultrazvukovoy-datchik-izmereniya-rasstoyaniya-hc-sr04/#h3_6)**

```C++
#include <iarduino_HC_SR04.h> // Подключаем библиотеку
iarduino_HC_SR04_int ОБЪЕКТ( ВЫВОД_TRIG , ВЫВОД_ECHO ); // Создаём объект.
```

**Расстояние в см** 

```C++
ОБЪЕКТ.distance( [ ТЕМПЕРАТУРА ] ); // Возвращает расстояние в см, принимая, в качестве необязательного параметра, температуру воздуха.
```

**Коэффициент усреднения** 

```C++
ОБЪЕКТ.averaging; // Положительное целое число - коэффициент усреднения показаний возвращаемых функцией distance().
```

