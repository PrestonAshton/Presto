#ifndef PRESTO_DEBUG_ASSERT_H
#define PRESTO_DEBUG_ASSERT_H

#include <Presto/Common/BasicDefinitions.h>
#include <Presto/Common/Types.h>

PSTDLIB_EXPORT void ForceAssert(const vchar* assertionText, const vchar* customMessage, const char* file, int lineNumber);

#ifdef _DEBUG
#define AssertMsg(x, y) \
	AssertActual(x, y, __FILE__, __LINE__)

#define FatalError(x, y) \
	AssertActual(x, y, __FILE__, __LINE__)

#define Assert(x) \
	AssertActual(x, NULL, __FILE__, __LINE__)

#define AssertActual(x, y, file, line) \
	if (!( x ) ) \
		ForceAssert( V(#x) , y , file, line );
#else

#define AssertMsg(x, y)

#define FatalError(x, y)

#define Assert(x)
}
#endif
#endif