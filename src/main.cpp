#include <Arduino.h>
#include "config.h"
#include "temperature.h"
#include "program_manager.h"
#include "user_interface.h"
#include "ota_updater.h"

// Таймеры для периодических задач
unsigned long lastTempUpdate = 0;
unsigned long lastDisplayUpdate = 0;
unsigned long lastProgramUpdate = 0;
unsigned long buttonPressTime = 0;

void setup() {
  // Инициализация последовательного порта для отладки
  Serial.begin(115200);
  Serial.println("TermoWood Thermostat Starting...");
  
  // Инициализация компонентов системы
  initTemperatureControl();
  initProgramManager();
  initUserInterface();
  initOTA();
  
  // Отображение приветствия
  Serial.println("TermoWood Thermostat Ready");
}

void loop() {
  unsigned long currentMillis = millis();
  
  // Обновление контроля температуры каждые 100 мс
  if (currentMillis - lastTempUpdate >= 100) {
    updateTemperatureControl();
    lastTempUpdate = currentMillis;
  }
  
  // Обновление отображения каждые 500 мс
  if (currentMillis - lastDisplayUpdate >= 500) {
    updateDisplay();
    lastDisplayUpdate = currentMillis;
  }
  
  // Обновление выполнения программы каждую секунду
  if (currentMillis - lastProgramUpdate >= 1000) {
    updateProgram();
    lastProgramUpdate = currentMillis;
  }
  
  // Обработка нажатий кнопок
  handleButtons();
  
  // Обработка OTA-обновлений
  handleOTA();
  
  // Проверка удержания кнопки SELECT для создания точки доступа OTA
  int button = getButton();
  if (button == 1) { // SELECT
    if (buttonPressTime == 0) {
      buttonPressTime = currentMillis;
    } else if (currentMillis - buttonPressTime >= 3000) {
      // Создаем точку доступа для OTA-обновления
      createOTAAP();
      buttonPressTime = 0;
    }
  } else {
    buttonPressTime = 0;
  }
}