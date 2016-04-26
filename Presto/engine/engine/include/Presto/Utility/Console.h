#ifndef PRESTO_UTILITY_CONSOLE_H
#define PRESTO_UTILITY_CONSOLE_H

#include <Presto/Graphics/Colour.h>

void OpenConsole(void);
void WriteToConsole(const vchar* string, Colour24 colour);
void WriteLineToConsole(const vchar* string, Colour24 colour);

#endif
