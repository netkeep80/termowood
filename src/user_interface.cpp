#include <Arduino.h>
#include "user_interface.h"
#include <Adafruit_RGBLCDShield.h>
#include <cstdio>
#include <cstring>

namespace {
Adafruit_RGBLCDShield lcd;
uint8_t currentButtonsState = 0;
char currentButtonName[17] = "Press a key";

int decodeButton(uint8_t buttons) {
  if (buttons & BUTTON_SELECT) {
    return 1;
  }
  if (buttons & BUTTON_UP) {
    return 2;
  }
  if (buttons & BUTTON_DOWN) {
    return 3;
  }
  if (buttons & BUTTON_LEFT) {
    return 4;
  }
  if (buttons & BUTTON_RIGHT) {
    return 5;
  }
  return 0;
}

const char* describeButtons(uint8_t buttons) {
  if (buttons & BUTTON_SELECT) {
    return "SELECT";
  }
  if (buttons & BUTTON_UP) {
    return "UP";
  }
  if (buttons & BUTTON_DOWN) {
    return "DOWN";
  }
  if (buttons & BUTTON_LEFT) {
    return "LEFT";
  }
  if (buttons & BUTTON_RIGHT) {
    return "RIGHT";
  }
  return "Press a key";
}

void printPadded(const char* text) {
  lcd.print(text);
  const size_t len = std::strlen(text);
  for (size_t i = len; i < 16; ++i) {
    lcd.print(' ');
  }
}

void setBacklightForButtons(uint8_t buttons) {
  if (buttons & BUTTON_SELECT) {
    lcd.setBacklight(0x1);
    return;
  }
  if (buttons & BUTTON_UP) {
    lcd.setBacklight(0x2);
    return;
  }
  if (buttons & BUTTON_DOWN) {
    lcd.setBacklight(0x4);
    return;
  }
  if (buttons & BUTTON_LEFT) {
    lcd.setBacklight(0x3);
    return;
  }
  if (buttons & BUTTON_RIGHT) {
    lcd.setBacklight(0x6);
    return;
  }
  lcd.setBacklight(0x7);
}
}

void initUserInterface() {
  lcd.begin(16, 2);
  lcd.setBacklight(0x7);

  lcd.clear();
  lcd.setCursor(0, 0);
  printPadded("TermoWood");
  lcd.setCursor(0, 1);
  printPadded("Button test");
  delay(1200);
}

void updateDisplay() {
  char line1[17];
  std::snprintf(line1, sizeof(line1), "Btn test %02X", currentButtonsState);

  lcd.setCursor(0, 0);
  printPadded(line1);
  lcd.setCursor(0, 1);
  printPadded(currentButtonName);
}

void handleButtons() {
  currentButtonsState = lcd.readButtons();
  std::snprintf(currentButtonName, sizeof(currentButtonName), "%s", describeButtons(currentButtonsState));
  setBacklightForButtons(currentButtonsState);
}

void showMainMenu() {
}

void showProgramStatus() {
}

void showProgramEditor() {
}

int getButton() {
  return decodeButton(currentButtonsState);
}
