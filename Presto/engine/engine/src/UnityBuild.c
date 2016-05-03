#pragma warning(push)

#pragma warning(disable: 4010)

#include <Presto/Presto.h>


#ifdef PRESTO_STEAM
#define STEAM(x) x
#else
#define STEAM(x)
#endif

#include "common/shared_engine.c"

#include "common/shared_glfuncs_generated.c"
#include "common/shared_glrenderpath.c"
#include "common/shared_camera.c"

#ifdef PRESTO_SYSTEM_WINDOWS

#include <Windows.h>
#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
// needed by opengl
#pragma comment(lib, "gdi32.lib")

#include "common/win32_input.c"
#include "common/win32_glwindow.c"

#include "common/win32_dx9window.c"
#include "common/win32_dx9renderpath.c"
#include "common/win32_console.c"
#include "common/win32_file.c"

#ifdef PRESTO_STEAM
#include "common/win32_steam.c"
#endif

//#ifdef PRESTO_MIDI
#include "common/win32_midi.c"
//#endif

#endif

#pragma warning(pop)
