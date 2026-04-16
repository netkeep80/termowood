#include "user_interface.h"
#include "program_manager.h"
#include "temperature.h"
#include <LiquidCrystal_I2C.h>
#include <LCD_RGB.h>

// Создаем объект для работы с LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Глобальные переменные для управления интерфейсом
int currentMenu = 0; // 0 - главное меню, 1 - статус программы, 2 - редактор программ
int selectedProgram = 0;
Program editingProgram;

// Инициализация пользовательского интерфейса
void initUserInterface() {
  // Инициализация LCD
  lcd.init();
  lcd.backlight();
  
  // Установка начального цвета подсветки
  lcd.setRGB(0, 255, 0); // Зеленый цвет - нормальная работа
  
  // Отображение начального экрана
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TermoWood");
  lcd.setCursor(0, 1);
  lcd.print("v1.0");
  delay(2000);
}

// Обновление отображения на LCD
void updateDisplay() {
  switch (currentMenu) {
    case 0:
      showMainMenu();
      break;
    case 1:
      showProgramStatus();
      break;
    case 2:
      showProgramEditor();
      break;
  }
}

// Обработка нажатий кнопок
void handleButtons() {
  int button = getButton();
  
  switch (currentMenu) {
    case 0: // Главное меню
      switch (button) {
        case 1: // SELECT
          if (isProgramRunning()) {
            stopProgram();
          } else {
            Program program;
            if (loadProgram(selectedProgram, program)) {
              startProgram(program);
            }
          }
          break;
        case 2: // UP
          selectedProgram = (selectedProgram + 1) % 10;
          break;
        case 3: // DOWN
          selectedProgram = (selectedProgram + 9) % 10;
          break;
        case 4: // LEFT
          // Переход к редактору программ
          currentMenu = 2;
          createNewProgram(editingProgram);
          break;
        case 5: // RIGHT
          // Переход к статусу программы
          currentMenu = 1;
          break;
      }
      break;
      
    case 1: // Статус программы
      if (button == 5) { // RIGHT - возврат в главное меню
        currentMenu = 0;
      }
      break;
      
    case 2: // Редактор программ
      if (button == 5) { // RIGHT - возврат в главное меню
        currentMenu = 0;
      }
      break;
  }
}

// Отображение главного меню
void showMainMenu() {
  lcd.clear();
  
  // Отображение выбранной программы
  lcd.setCursor(0, 0);
  lcd.print("Prog: ");
  lcd.print(selectedProgram);
  
  // Отображение статуса выполнения
  lcd.setCursor(0, 1);
  if (isProgramRunning()) {
    lcd.print("RUNNING");
  } else {
    lcd.print("STOPPED");
  }
  
  // Отображение информации о программе
  Program program;
  if (loadProgram(selectedProgram, program)) {
    lcd.setCursor(9, 0);
    lcd.print(program.name);
    lcd.setCursor(9, 1);
    lcd.print(program.numStages);
    lcd.print(" stages");
  } else {
    lcd.setCursor(9, 0);
    lcd.print("Empty");
  }
}

// Отображение статуса выполнения программы
void showProgramStatus() {
  lcd.clear();
  
  if (isProgramRunning()) {
    // Отображение текущего этапа и оставшегося времени
    lcd.setCursor(0, 0);
    lcd.print("Stage: ");
    lcd.print(getCurrentStage() + 1);
    lcd.print("/");
    lcd.print(currentProgram.numStages);
    
    lcd.setCursor(0, 1);
    lcd.print("Time: ");
    unsigned int remaining = getRemainingTime();
    lcd.print(remaining / 60);
    lcd.print(":");
    if (remaining % 60 < 10) {
      lcd.print("0");
    }
    lcd.print(remaining % 60);
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Program stopped");
  }
}

// Отображение редактора программ
void showProgramEditor() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Program Editor");
  lcd.setCursor(0, 1);
  lcd.print("Not implemented");
}

// Получение нажатой кнопки
int getButton() {
  // TODO: Реализовать чтение нажатий кнопок с LCD модуля
  // Временная реализация - возврат 0 (нет нажатий)
  return 0;
}