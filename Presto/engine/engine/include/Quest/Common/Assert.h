#ifndef QUEST_DEBUG_ASSERT_H
#define QUEST_DEBUG_ASSERT_H

#include <Quest/Common/BasicDefinitions.h>
#include <Quest/Common/Types.h>

forceinline void ForceAssert(const vchar* assertionText, const vchar* customMessage, const char* file, int lineNumber, b8* ignore);

#ifdef _DEBUG

#define AssertMsg(x, y) \
	AssertActual(x, y, __FILE__, __LINE__)

#define FatalError(x, y) \
	AssertActual(x, y, __FILE__, __LINE__)

#define Assert(x) \
	AssertActual(x, NULL, __FILE__, __LINE__)

#define AssertActual(x, y, file, line) \
	static b8 ASSERTBLOCK##line = false; \
	if (!( x )) \
		ForceAssert( V(#x) , y , file, line, & ASSERTBLOCK##line );
#else

#define AssertMsg(x, y)

#define FatalError(x, y)

#define Assert(x)
#endif
#endif
