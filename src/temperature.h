#ifndef TEMPERATURE_H
#define TEMPERATURE_H

// Инициализация системы контроля температуры
void initTemperatureControl();

// Чтение температуры с датчиков
float readTemperature1();
float readTemperature2();

// Получение максимальной температуры из двух датчиков
float getMaxTemperature();

// Установка целевой температуры для PID-регулятора
void setTargetTemperature(float target);

// Обновление PID-регулятора и управление нагревом
void updateTemperatureControl();

// Отключение нагрева
void disableHeating();

#endif