#include <Presto/Presto.h>

#ifdef PRESTO_STEAM
#define STEAM(x) x
#else
#define STEAM(x)
#endif

#ifdef PRESTO_SYSTEM_WINDOWS
#include <Windows.h>
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
// needed by opengl
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "winmm.lib")

#include "common/win32_input.c"
#endif

#include "common/shared_engine.c"

#include "common/shared_glfuncs_generated.c"
#include "common/shared_glrenderpath.c"
#include "common/shared_camera.c"
#include "common/win32_glwindow.c"

#ifdef PRESTO_STEAM
#include "common/win32_steam.c"
#endif

//#ifdef PRESTO_MIDI
#include "common/win32_midi.c"
//#endif
