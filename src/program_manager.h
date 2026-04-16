#ifndef PROGRAM_MANAGER_H
#define PROGRAM_MANAGER_H

#include "config.h"

void initProgramManager();
bool loadProgram(int programNumber, Program& program);
bool saveProgram(int programNumber, const Program& program);
void createNewProgram(Program& program);
void startProgram(const Program& program);
void stopProgram();
bool isProgramRunning();
int getCurrentStage();
Program getCurrentProgram();
unsigned int getRemainingTime();
void updateProgram();

#endif
