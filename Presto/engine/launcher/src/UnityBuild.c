#include <Quest/Common.h>
#include <Quest/Engine/Engine.h>

#ifdef QUEST_SYSTEM_WINDOWS

DISABLE_WARNINGS
#include <Windows.h>
#include <Shlwapi.h>
ENABLE_WARNINGS

#pragma comment(lib, "Shlwapi.lib")

#include "win32_mainnew.c"
#endif
