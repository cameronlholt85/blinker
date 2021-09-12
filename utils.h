#include "TinyI2C.h"

void SetClock(int hour, int min, int sec);

void WriteCommand(int commandArray[], uint8_t commandArraySize);

void WriteSingleCommand(int command);

// Write a single command
void Single(uint8_t x);

void String(char *string, int length);

bool digitalRead(void);

void updateDisplay(int hh, int mm);