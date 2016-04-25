#ifndef PRESTO_COMMON_BASICDEFINITIONS_H
#define PRESTO_COMMON_BASICDEFINITIONS_H

#include <Presto/Common/Compilers.h>

#ifndef NULL
#define NULL 0
#endif

#if defined( PSTDLIB_EXPORTS )
#define PSTDLIB_EXPORT __declspec(dllexport)
#else
#define PSTDLIB_EXPORT __declspec(dllimport)
#endif


#if defined( PRESTO_EXPORTS )
#define PRESTO_EXPORT __declspec(dllexport)
#else
#define PRESTO_EXPORT __declspec(dllimport)
#endif

#ifdef _DEBUG
#define DEBUG_EXPORT __declspec(dllexport)
#else
#define DEBUG_EXPORT
#endif

#ifdef PRESTO_COMPILER_MSVC
#define forceinline __forceinline
#else
#define forceinline __attribute__ ((__always_inline__))
#endif

#define maybeinline inline
#define false 0
#define true 1

#define LOCK_MUTEX(x) \
	while (heapMutex = true) \
	{} \
	heapMutex = true

#define UNLOCK_MUTEX(x) \
	heapMutex = false

PSTDLIB_EXPORT int BlankFunction(void);

#define FULFIL_INTERFACE_FUNCTION(name, returnType, ...) \
	__declspec(dllexport) returnType name##( ##__VA_ARGS__## )

#define DEFINE_EXTERNAL_INTERFACE_FUNCTION(name, returnType, ...) \
	const char* PRESTO_FUNCTIONINTERFACE_##name##_NAME = #name; \
	typedef returnType (*name##Function)( ##__VA_ARGS__## ) \

#define DEFINE_INTERFACE_FUNCTION(name, returnType, ...) \
	__declspec(dllexport) returnType name##( ##__VA_ARGS__## ); \
	const char* PRESTO_FUNCTIONINTERFACE_##name##_NAME = #name; \
	typedef returnType (*name##Function)( ##__VA_ARGS__## )

#define GET_INTERFACE_TYPE(name) \
	name##Function

#define GET_INTERFACE_NAME(name) \
	PRESTO_FUNCTIONINTERFACE_##name##_NAME

#undef DEBUG

#ifdef _DEBUG
#define DEBUG(x) x
#else
#define DEBUG(x)
#endif

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))


#ifdef defined(_MSC_VER)
#pragma section(".CRT$XCU",read)
#define INITIALIZER2_(f,p) \
        static void f(void); \
        __declspec(allocate(".CRT$XCU")) void (*f##_)(void) = f; \
        __pragma(comment(linker,"/include:" p #f "_")) \
        static void f(void)
#ifdef _WIN64
#define INITIALIZER(f) INITIALIZER2_(f,"")
#else
#define INITIALIZER(f) INITIALIZER2_(f,"_")
#endif
#else
#define INITIALIZER(f) \
        static void f(void) __attribute__((constructor)); \
        static void f(void)
#endif

#endif
