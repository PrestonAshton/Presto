#ifndef QUEST_COMMON_BASICDEFINITIONS_H
#define QUEST_COMMON_BASICDEFINITIONS_H

#include <Quest/Common/Compilers.h>

#ifndef NULL
#define NULL 0
#endif

#ifdef QUEST_STEAM
#define STEAM(x) x
#else
#define STEAM(x)
#endif

#define DISABLE_WARNINGS __pragma(warning(push, 0))
#define ENABLE_WARNINGS __pragma(warning(pop))

#ifdef QUEST_COMPILER_MSVC

DISABLE_WARNINGS
#include <intrin.h>
ENABLE_WARNINGS

#define ENDIAN_SWAP16(x) _byteswap_ushort(x);
#define ENDIAN_SWAP32(x) _byteswap_ulong(x);
#define ENDIAN_SWAP64(x) _byteswap_uint64(x);
#endif

#define BLANK_FUNCTION(x) x() {}

#if defined( QUEST_EXPORTS )
#define QUEST_EXPORT __declspec(dllexport)
#else
#define QUEST_EXPORT __declspec(dllimport)
#endif

#ifdef _DEBUG
#define DEBUG_EXPORT __declspec(dllexport)
#else
#define DEBUG_EXPORT
#endif

#ifdef QUEST_COMPILER_MSVC
#define forceinline __forceinline
#else
#define forceinline __attribute__ ((__always_inline__))
#endif

#define maybeinline inline
#define false 0
#define true 1

#define hash(x) murmur64( x , strlen(x) )
#define hashCustomLength(x, length) murmur64( x , length )

#define LOCK_MUTEX(x) \
	while (heapMutex == true) \
	{} \
	heapMutex = true

#define UNLOCK_MUTEX(x) \
	heapMutex = false

void BlankFunction(void);

#define FULFIL_INTERFACE_FUNCTION(name, returnType, ...) \
	__declspec(dllexport) returnType name##( ##__VA_ARGS__## )

#define DEFINE_EXTERNAL_INTERFACE_FUNCTION(name, returnType, ...) \
	const char* QUEST_FUNCTIONINTERFACE_##name##_NAME = #name; \
	typedef returnType (*name##Function)( ##__VA_ARGS__## ) \

#define DEFINE_INTERFACE_FUNCTION(name, returnType, ...) \
	__declspec(dllexport) returnType name##( ##__VA_ARGS__## ); \
	const char* QUEST_FUNCTIONINTERFACE_##name##_NAME = #name; \
	typedef returnType (*name##Function)( ##__VA_ARGS__## )

#define GET_INTERFACE_TYPE(name) \
	name##Function

#define GET_INTERFACE_NAME(name) \
	QUEST_FUNCTIONINTERFACE_##name##_NAME

#undef DEBUG

#ifdef _DEBUG
#define DEBUG(x) x
#else
#define DEBUG(x)
#endif

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define KILOBYTES(x) ((x) * 1024LL)
#define MEGABYTES(x) ((KILOBYTES(x) * 1024LL)
#define GIGABYTES(x) ((MEGABYTES(x) * 1024LL)
#define TERABYTES(x) ((GIGABYTES(x) * 1024LL)
#define PETABYTES(x) ((TERABYTES(x) * 1024LL)
#define EXABYTES(x) ((PETABYTES(x) * 1024LL)
#define ZETTABYTES(x) ((EXABYTES(x) * 1024LL)
#define YOTTABYTES(x) ((ZETTABYTES(x) * 1024LL)

#define STATIC_ASSERT(COND,MSG) typedef char static_assertion_##MSG[(COND)?1:-1]

#define __STATIC_MESSAGE(Message) __pragma( message( #Message ) )
#define _STATIC_MESSAGE(Message) __STATIC_MESSAGE(Message)
#define STATIC_MESSAGE(Message) _STATIC_MESSAGE( [Message] )

#ifdef QUEST_COMPILER_MSVC

#define PACK( __Declaration__ ) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop) )

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

#define PACK( __Declaration__ ) __Declaration__ __attribute__((__packed__))

#define INITIALIZER(f) \
        static void f(void) __attribute__((constructor)); \
        static void f(void)
#endif

#ifdef QUEST_COMPILER_MSVC
#define dontinline __declspec(noinline)
#else
#define dontinline __attribute__((noinline))
#endif

#define WORDSWAP(w)		(((w) >> 8) | \
						(((w) << 8) & 0xFF00))

#define DWORDSWAP(dw)	(((dw) >> 24) | \
						(((dw) >> 8) & 0x0000FF00) | \
						(((dw) << 8) & 0x00FF0000) | \
						(((dw) << 24) & 0xFF000000))

#ifdef QUEST_COMPILER_MSVC
#define ALIGNOF(x) __alignof(x)
#define TYPEOF(x) __typeof(x)
#else
#define ALIGNOF(x) alignof(x)
#define TYPEOF(x) typeof(x)
#endif


#endif
