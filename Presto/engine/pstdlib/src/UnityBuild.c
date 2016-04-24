#include <Presto/pstdlib.h>

#include "common/shared_common.c"
#include "common/shared_memory.c"
#include "common/shared_math.c"

#ifdef PRESTO_SYSTEM_WINDOWS
#include <Windows.h>
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")

#include "common/win32_common.c"
#endif
