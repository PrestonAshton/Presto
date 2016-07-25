#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <windows.h>
#include <stdarg.h>
#include <wchar.h>


HANDLE handle_out;
HANDLE handle_in;

CONSOLE_SCREEN_BUFFER_INFO csbi;

void OpenConsole(void)
{
	AllocConsole();

	handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
	int hCrt = _open_osfhandle((long)handle_out, _O_TEXT);
	FILE* hf_out = _fdopen(hCrt, "w");
	setvbuf(hf_out, NULL, _IONBF, 1);
	*stdout = *hf_out;

	handle_in = GetStdHandle(STD_INPUT_HANDLE);
	hCrt = _open_osfhandle((long)handle_in, _O_TEXT);
	FILE* hf_in = _fdopen(hCrt, "r");
	setvbuf(hf_in, NULL, _IONBF, 128);
	*stdin = *hf_in;

	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);

	SetConsoleTitle(V("Quest Developer Console"));
	SetConsoleOutputCP(65001);
}

void WriteToConsole(ConsoleColour colour, const vchar* fmt, ...)
{
	usize textLength = Vstrlen(fmt);
	vchar* textBuffer[1024];

	va_list args;
	va_start(args, fmt);
	Vvsprintf(textBuffer, 1024, fmt, args);
	va_end(args);

	SetConsoleTextAttribute(handle_out, colour);

	WriteConsole(handle_out, textBuffer, textLength, NULL, NULL);
}

void UpdateConsole(void)
{
	if (KeyPressed(GraveAccent, Single))
		OpenConsole();
}

void WriteLineToConsole(ConsoleColour colour, const vchar* fmt, ...)
{
	usize textLength = Vstrlen(fmt);
	usize textSize = (textLength + 2) * sizeof(vchar);
	vchar* textBuffer = malloc(textSize);
	copyMemory(fmt, textBuffer, textSize);
	textBuffer[textLength] = V('\n');
	textBuffer[textLength + 1] = V('\0');

	va_list args;
	va_start(args, fmt);
	WriteToConsole(colour, fmt, args);
	va_end(args);
}
