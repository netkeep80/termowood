#include "config.h"
#include <max6675.h>
#include <PID_v1.h>

// Создаем объекты для работы с термопарами MAX6675
MAX6675 thermocouple1(MAX6675_1_SCK, MAX6675_1_CS, MAX6675_1_SO);
MAX6675 thermocouple2(MAX6675_2_SCK, MAX6675_2_CS, MAX6675_2_SO);

// Переменные для PID-регулятора
double setpoint, input, output;
double kp = 2, ki = 5, kd = 1;
PID pid(&input, &output, &setpoint, kp, ki, kd, DIRECT);

// Инициализация системы контроля температуры
void initTemperatureControl() {
  // Инициализация пина управления нагревом
  pinMode(SSR_PIN, OUTPUT);
  digitalWrite(SSR_PIN, LOW);
  
  // Инициализация PID-регулятора
  pid.SetMode(AUTOMATIC);
  pid.SetOutputLimits(0, 1023); // Пределы ШИМ для ESP8266
}

// Чтение температуры с обоих датчиков
float readTemperature1() {
  return thermocouple1.readCelsius();
}

float readTemperature2() {
  return thermocouple2.readCelsius();
}

// Получение максимальной температуры из двух датчиков
float getMaxTemperature() {
  float temp1 = readTemperature1();
  float temp2 = readTemperature2();
  
  // Проверка на обрыв термопары
  if (temp1 >= 1024 || temp2 >= 1024) {
    // Обработка ошибки обрыва термопары
    return -1; // Сигнал об ошибке
  }
  
  return (temp1 > temp2) ? temp1 : temp2;
}

// Установка целевой температуры для PID-регулятора
void setTargetTemperature(float target) {
  setpoint = target;
}

// Обновление PID-регулятора и управление нагревом
void updateTemperatureControl() {
  // Чтение текущей температуры (максимальной из двух датчиков)
  input = getMaxTemperature();
  
  // Проверка на ошибки датчиков
  if (input < 0) {
    // Отключаем нагрев при ошибке датчиков
    digitalWrite(SSR_PIN, LOW);
    return;
  }
  
  // Вычисление нового значения PID
  pid.Compute();
  
  // Управление нагревом через ШИМ
  analogWrite(SSR_PIN, output);
  
  // Проверка на превышение максимальной температуры
  if (input > MAX_TEMPERATURE) {
    // Отключаем нагрев при превышении максимальной температуры
    digitalWrite(SSR_PIN, LOW);
  }
}

// Отключение нагрева
void disableHeating() {
  digitalWrite(SSR_PIN, LOW);
  output = 0;
}