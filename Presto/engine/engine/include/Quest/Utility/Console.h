#ifndef QUEST_UTILITY_CONSOLE_H
#define QUEST_UTILITY_CONSOLE_H

#include <Quest/Graphics/Colour.h>

DISABLE_WARNINGS
#include <time.h>
ENABLE_WARNINGS

typedef enum
{
	DarkBlue = 1,
	DarkGreen = 2,
	DarkCyan,
	DarkRed,
	DarkPink,
	DarkYellow,
	DarkWhite,
	DarkGrey,
	BrightBlue,
	BrightGreen,
	BrightCyan,
	BrightRed,
	BrightPink,
	BrightYellow,
	BrightWhite,
} ConsoleColour;

void OpenConsole(void);

void WriteToConsole(ConsoleColour colour, const vchar* fmt, ...);
void WriteLineToConsole(ConsoleColour colour, const vchar* fmt, ...);

void UpdateConsole(void);

maybeinline void MessageToConsole(ConsoleColour prefixColour, const vchar* prefixName, ConsoleColour fmtColour, const vchar* fmt, ...)
{
	vchar buffer[64];
	time_t secondsCeiling = time(NULL);
	struct tm* time = localtime((&secondsCeiling));
	Vstrftime(buffer, 64, V("%H:%M:%S"), time);

	WriteToConsole(BrightWhite, buffer, NULL);
	WriteToConsole(BrightWhite, V(" ["), NULL);
	WriteToConsole(prefixColour, prefixName, NULL);
	WriteToConsole(BrightWhite, V("] "), NULL);
	va_list args;
	va_start(args, fmt);
	WriteLineToConsole(fmtColour, fmt, args);
	va_end(args);
}

#define FAIL(fmt, ...) \
	MessageToConsole(BrightRed, V("FAIL"), BrightRed, fmt, __VA_ARGS__)

#define OK(fmt, ...) \
	MessageToConsole(BrightGreen, V("OKAY"), BrightWhite, fmt, __VA_ARGS__)

#define MSG(fmt, ...) \
	MessageToConsole(BrightCyan, V("MESG"), BrightWhite, fmt, __VA_ARGS__)

#define WARN(fmt, ...) \
	MessageToConsole(BrightYellow, V("WARN"), BrightYellow, fmt, __VA_ARGS__)

#define DBUG(fmt, ...) \
	MessageToConsole(BrightPink, V("DBUG"), BrightWhite, fmt, __VA_ARGS__)

#endif
