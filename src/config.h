#ifndef CONFIG_H
#define CONFIG_H

// Пины подключения термопар MAX6675
#define MAX6675_1_SCK D5
#define MAX6675_1_SO  D6
#define MAX6675_1_CS  D4

#define MAX6675_2_SCK D5
#define MAX6675_2_SO  D6
#define MAX6675_2_CS  D0

// Пины подключения LCD
#define LCD_SDA D4
#define LCD_SCL D5

// Пин управления нагревом через SSR
#define SSR_PIN D3

// Максимальная температура для древесины
#define MAX_TEMPERATURE 200.0

// Количество этапов в программе термообработки
#define MAX_STAGES 9

// Структура для хранения данных о каждом этапе программы
struct Stage {
  unsigned int duration; // Продолжительность в минутах
  float temperature;      // Целевая температура в градусах Цельсия
};

// Структура для хранения программы термообработки
struct Program {
  char name[20];          // Название программы
  unsigned int numStages; // Количество этапов
  Stage stages[MAX_STAGES]; // Массив этапов
};

#endif