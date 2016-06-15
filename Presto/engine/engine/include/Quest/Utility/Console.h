#ifndef QUEST_UTILITY_CONSOLE_H
#define QUEST_UTILITY_CONSOLE_H

#include <Quest/Graphics/Colour.h>

void OpenConsole(void);
void WriteToConsole(const vchar* string, Colour24 colour);
void WriteLineToConsole(const vchar* string, Colour24 colour);

#endif
