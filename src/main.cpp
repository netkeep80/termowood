#include <Arduino.h>
#include "user_interface.h"

namespace {
unsigned long lastDisplayUpdate = 0;
}

void setup() {
  Serial.begin(115200);
  Serial.println("TermoWood button test starting...");
  initUserInterface();
  Serial.println("TermoWood button test ready");
}

void loop() {
  const unsigned long currentMillis = millis();

  handleButtons();

  if (currentMillis - lastDisplayUpdate >= 100) {
    updateDisplay();
    lastDisplayUpdate = currentMillis;
  }
}
