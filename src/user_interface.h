#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include "config.h"

void initUserInterface();
void updateDisplay();
void handleButtons();
void showMainMenu();
void showProgramStatus();
void showProgramEditor();
int getButton();

#endif
