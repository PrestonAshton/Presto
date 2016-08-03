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

void WriteToConsole(ConsoleColour colour, const vchar* fmt, va_list args)
{
	u32 size = Vvsnprintf(NULL, 0, fmt, args) + 1;
	vchar* buffer = spawn(size * sizeof(vchar));
	Vvsprintf(buffer, size, fmt, args);
	SetConsoleTextAttribute(handle_out, colour);
	WriteConsole(handle_out, buffer, size - 1, NULL, NULL);
}

void WriteLineToConsole(ConsoleColour colour, const vchar* fmt, va_list args)
{
	u32 fmtSize = Vstrlen(fmt);
	vchar* buffer = conjure((fmtSize + 2) * sizeof(vchar));
	copyMemory(fmt, buffer, (fmtSize) * sizeof(vchar));
	buffer[fmtSize] = V('\n');
	buffer[fmtSize + 1] = V('\0');
	WriteToConsole(colour, buffer, args);
}
