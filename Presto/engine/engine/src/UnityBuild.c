#pragma warning(disable: 4010)

#include <Quest/Quest.h>

// Platform independent code!
// ***FOR -ALL- PLATFORMS***
#include "shared/UnityBuild.c"

#ifdef QUEST_SYSTEM_WINDOWS
#include "win32/UnityBuild.c"
#endif

#ifdef QUEST_SYSTEM_LINUX
#include "linux/UnityBuild.c"
#endif


#pragma warning(pop)
