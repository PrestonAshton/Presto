#include <Presto/Presto.h>

#ifdef PRESTO_SYSTEM_WINDOWS
#include <Windows.h>
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")

#include "win32_main.c"
#endif
