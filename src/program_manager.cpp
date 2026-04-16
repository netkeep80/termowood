#include "program_manager.h"
#include "temperature.h"
#include <EEPROM.h>

// Глобальные переменные для отслеживания состояния программы
bool programRunning = false;
unsigned long programStartTime = 0;
unsigned long stageStartTime = 0;
int currentStage = 0;
unsigned int remainingTime = 0;
Program currentProgram;

// Инициализация менеджера программ
void initProgramManager() {
  // Инициализация EEPROM
  EEPROM.begin(sizeof(Program) * 10); // Резервируем место для 10 программ
}

// Загрузка программы из EEPROM
bool loadProgram(int programNumber, Program& program) {
  if (programNumber < 0 || programNumber >= 10) {
    return false;
  }
  
  // Читаем программу из EEPROM
  EEPROM.get(sizeof(Program) * programNumber, program);
  
  // Проверяем, была ли программа сохранена ранее
  if (program.numStages == 0 || program.numStages > MAX_STAGES) {
    return false;
  }
  
  return true;
}

// Сохранение программы в EEPROM
bool saveProgram(int programNumber, const Program& program) {
  if (programNumber < 0 || programNumber >= 10) {
    return false;
  }
  
  // Записываем программу в EEPROM
  EEPROM.put(sizeof(Program) * programNumber, program);
  EEPROM.commit();
  
  return true;
}

// Создание новой программы
void createNewProgram(Program& program) {
  // Инициализируем структуру программы
  strcpy(program.name, "Новая программа");
  program.numStages = 0;
  
  // Инициализируем этапы
  for (int i = 0; i < MAX_STAGES; i++) {
    program.stages[i].duration = 0;
    program.stages[i].temperature = 0.0;
  }
}

// Запуск выполнения программы
void startProgram(const Program& program) {
  // Копируем программу в текущую
  currentProgram = program;
  
  // Сбрасываем состояние выполнения
  programRunning = true;
  programStartTime = millis();
  currentStage = 0;
  
  // Устанавливаем время начала первого этапа
  stageStartTime = millis();
  remainingTime = currentProgram.stages[0].duration * 60; // Переводим минуты в секунды
  
  // Устанавливаем целевую температуру для первого этапа
  setTargetTemperature(currentProgram.stages[0].temperature);
}

// Остановка выполнения программы
void stopProgram() {
  programRunning = false;
  disableHeating();
}

// Проверка, выполняется ли программа
bool isProgramRunning() {
  return programRunning;
}

// Получение текущего этапа программы
int getCurrentStage() {
  return currentStage;
}

// Получение оставшегося времени на текущем этапе (в секундах)
unsigned int getRemainingTime() {
  return remainingTime;
}

// Обновление выполнения программы
void updateProgram() {
  // Проверяем, выполняется ли программа
  if (!programRunning) {
    return;
  }
  
  // Вычисляем прошедшее время на текущем этапе
  unsigned long elapsedTime = (millis() - stageStartTime) / 1000;
  
  // Проверяем, не закончилось ли время на текущем этапе
  if (elapsedTime >= remainingTime) {
    // Переходим к следующему этапу
    currentStage++;
    
    // Проверяем, не закончилась ли программа
    if (currentStage >= currentProgram.numStages) {
      // Программа завершена
      stopProgram();
      return;
    }
    
    // Начинаем следующий этап
    stageStartTime = millis();
    remainingTime = currentProgram.stages[currentStage].duration * 60;
    
    // Устанавливаем целевую температуру для следующего этапа
    setTargetTemperature(currentProgram.stages[currentStage].temperature);
  } else {
    // Обновляем оставшееся время
    remainingTime = currentProgram.stages[currentStage].duration * 60 - elapsedTime;
  }
}