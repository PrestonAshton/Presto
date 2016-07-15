#ifndef QUEST_COMMON_WINDOWS_H
#define QUEST_COMMON_WINDOWS_H

#include <Quest/Common/Types.h>
#include <Quest/Common/Architectures.h>
#include <Quest/Common/BasicDefinitions.h>
#include <Quest/Memory/Memory.h>

DISABLE_WARNINGS
#include <Windows.h>
ENABLE_WARNINGS

forceinline vchar* GetLastErrorAsString(void)
{
	vchar* messageBuffer = conjure(512 * sizeof(vchar));
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), messageBuffer, 512, NULL);
	return(messageBuffer);
}

#endif