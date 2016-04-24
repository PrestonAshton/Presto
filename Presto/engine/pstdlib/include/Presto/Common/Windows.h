#ifndef PRESTO_COMMON_WINDOWS_H
#define PRESTO_COMMON_WINDOWS_H

#include <Presto/Common/Charsets.h>
#include <Presto/Common/Architectures.h>
#include <Presto/Common/BasicDefinitions.h>
#include <Presto/Memory/Memory.h>
#include <Windows.h>

forceinline vchar* GetLastErrorAsString(void)
{
	vchar* messageBuffer = conjure(512 * sizeof(vchar));
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), messageBuffer, 512, NULL);
	return(messageBuffer);
}

#endif