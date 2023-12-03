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
8) ЦАП : У многих платы приходят с не распаянными мостиками, как было к примеру и у меня.
На задней стороне (не компонентная сторона) расположены 4 набора по 3 площадки для 4 функций:
FLT - выбор фильтра: нормальная задержка (LO) / низкая задержка (HI)
DEMP - управление De-emphasis для частоты дискретизации 44,1 кГц: Off (LO) / On (HI)
XSMT - Управление мягким приглушением звука (Soft Mute)(1): Soft Mute (LO) / без Soft Mute (HI)
FMT - Выбор формата аудио: I2S (LO) / Выровненное по левому (HI)
Центральная площадка подключена к соответствующему выводу. Каждая из этих площадок может быть соединена припоем с высоким (HI) или низким уровнем (LO) 
(или иными словами контакты подключены к +3,3 В / 0 В).

Примеры распайки:
1, 2 и 4 - LO, и 3, соединенный HI, т.е. фильтр с нормальной задержкой, де-эмфазис 44,1 кГц отключен, soft-mute не применяется, аудиоформат I2S).
Нормальный фильтр - это FIR с хорошим откликом, задерживающий сигнал примерно на 500us (при 44,1 кГц), что должно быть нормально. Быстрый фильтр 
это IIR с немного худшим откликом, задерживающий сигнал примерно на 80us. Очень немногие (если вообще есть) источники звука имеют предварительный 
эмфазис, поэтому DEMP должен быть низким. Вывод XSMT позволит отключить звук на выходе через GPI (если удалить паяльный мост). ESP32 поддерживает 
битовый поток I2S, поэтому FMT должен быть низким. 

Пояснение из WIKI по функции DEMP:
В обработке сигналов предэмфаза (pre-emphasis)- это техника, используемая для защиты от ожидаемого шума. Идея заключается в усилении (и, следовательно, 
искажении) частотного диапазона, наиболее подверженного шуму, заранее, чтобы после процесса с шумом (передача по кабелю, запись на ленту и т. д.) из 
этого частотного диапазона можно было извлечь больше информации. Устранение искажений, вызванных pre-emphasis, называется De-emphasis, что позволяет 
точнее воспроизводить оригинальный входной сигнал.
