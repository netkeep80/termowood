#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include "config.h"
#include <LiquidCrystal_I2C.h>

// Инициализация пользовательского интерфейса
void initUserInterface();

// Обновление отображения на LCD
void updateDisplay();

// Обработка нажатий кнопок
void handleButtons();

// Отображение главного меню
void showMainMenu();

// Отображение статуса выполнения программы
void showProgramStatus();

// Отображение редактора программ
void showProgramEditor();

// Получение нажатой кнопки
int getButton();

#endif