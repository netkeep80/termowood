#ifndef PROGRAM_MANAGER_H
#define PROGRAM_MANAGER_H

#include "config.h"

// Инициализация менеджера программ
void initProgramManager();

// Загрузка программы из EEPROM
bool loadProgram(int programNumber, Program& program);

// Сохранение программы в EEPROM
bool saveProgram(int programNumber, const Program& program);

// Создание новой программы
void createNewProgram(Program& program);

// Запуск выполнения программы
void startProgram(const Program& program);

// Остановка выполнения программы
void stopProgram();

// Проверка, выполняется ли программа
bool isProgramRunning();

// Получение текущего этапа программы
int getCurrentStage();

// Получение оставшегося времени на текущем этапе (в секундах)
unsigned int getRemainingTime();

// Обновление выполнения программы
void updateProgram();

#endif