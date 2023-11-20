# BendeRadio
 Интернет-радио в форме головы Бендера

Проект сконфигурирован под VSCode. Как отконфигурировать VSCode для работы с ESP32 подробно описано тут:
https://randomnerdtutorials.com/vs-code-platformio-ide-esp32-esp8266-arduino/

Изменения:
1) Переделано подключение к WIFI сетям, выбором лучшей по мощности сигнала. За основу взят алгоритм из библиотеки
WiFiMulti.
2) Добавлены mutex блокировки в 2 функции управления матрицами.
3) Понижена скорость SPI: #define MAX_SPI_SPEED 250000

Часто задаваемые вопросы:
1) Матрицы заказывать только с общим катодом.
2) В списке "Железки со схемы" не указан энкодер для Arduino. Ключевые слова для поиска на али: 
Rotary Encoder Module for Arduino.
3) Винты на M4 необходимо брать длинной 60mm, а не 50mm как было указано в видео.
4) Если при компиляции оригинальной прошивки не находит GyverMax7219.h, заменить на
GyverMAX7219.h.
5) Можно использовать ESP32 c 30 PINs, а не с 38, как указано по ссылке.
6) Уровень свиста сильно зависит от яркости матриц. При понижении яркости до минимально помех практически не
слышно даже без добавления конденсаторов.
7) По схеме не CMD, а GND. См. исправленный файл scheme2.jpg
