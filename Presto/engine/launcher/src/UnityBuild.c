#include <Quest/Quest.h>

#ifdef QUEST_SYSTEM_WINDOWS

DISABLE_WARNINGS
#include <Windows.h>
#include <Shlwapi.h>
ENABLE_WARNINGS

#pragma comment(lib, "Shlwapi.lib")

#include "win32_main.c"
#endif
