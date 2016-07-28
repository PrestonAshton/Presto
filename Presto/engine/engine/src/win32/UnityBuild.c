DISABLE_WARNINGS
#include <Windows.h>
#include <Shlwapi.h>
ENABLE_WARNINGS

#include "win32/common.c"
#include "win32/console.c"
#include "win32/dx9renderpath.c"
#include "win32/dx9window.c"
#include "win32/file.c"
#include "win32/time.c"
#include "win32/input.c"
#include "win32/window.c"

#ifdef QUEST_STEAM
#include "win32/steam.c"
#endif

#pragma comment(lib, "Shlwapi.lib") // Basic functions and that in Windows below.
#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib") // Needed for OpenGL and the console.
#pragma comment(lib, "Winmm.lib") // Needed for TimeSleep