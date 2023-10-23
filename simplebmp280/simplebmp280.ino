#include <SPI.h>
// Подключаем библиотеки для работы с датчиком BMP280
#include <Wire.h>
#include <Adafruit_BMP280.h>
Adafruit_BMP280 bmp;

uint8_t pp[84]; // Массив значений атм. давления для вывода графика
uint8_t index = 0; // Текущий индекс (точка на графике)

void setup() {
  bmp.begin(); // Инициализация датчика BMP280
  // Настройка режима работы датчика BMP280
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,
                  Adafruit_BMP280::SAMPLING_X2,
                  Adafruit_BMP280::SAMPLING_X16,
                  Adafruit_BMP280::FILTER_X16,
                  Adafruit_BMP280::STANDBY_MS_500);
  for(uint8_t i = 0; i < 84; i++) pp[i] = 0; // Обнуляем массив
  Serial.begin(9600);
}

void loop() {
  // Считываем и выводим показания температуры
  float t = bmp.readTemperature();
  Serial.println(t);
  delay(500);
}
