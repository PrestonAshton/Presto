#ifndef QUEST_COMMON_TYPES_H
#define QUEST_COMMON_TYPES_H

#include <Quest/Common/BasicDefinitions.h>
#include <Quest/Common/Architectures.h>
#include <Quest/Common/Compilers.h>

DISABLE_WARNINGS
#include <stdio.h>
ENABLE_WARNINGS

typedef char a8;
typedef short a16;
typedef long a32;
typedef long long a64;

typedef signed char i8;
typedef signed short i16;
typedef signed long i32;
typedef signed long long i64;

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef unsigned long long u64;

typedef float f32;
typedef double f64;
typedef long double f128;

#if !QUEST_MAXINT_BITS
#elif QUEST_MAXINT_BITS == 64
typedef u64 usize;
typedef i64 isize;
#elif QUEST_MAXINT_BITS == 32
typedef u32 usize;
typedef i32 isize;
#elif QUEST_MAXINT_BITS == 16
typedef u16 usize;
typedef i16 isize;
#elif QUEST_MAXINT_BITS == 8
typedef u8 usize;
typedef i8 isize;
#endif

typedef isize iptr;
typedef usize uptr;

typedef i8 b8;
typedef b8 bool;

#if defined(UNICODE)
#define QUEST_CHARSET_UNICODE
#else
#define QUEST_CHARSET_ANSI
#endif

#define _W(string) L ## string
#define W(string) _W(string)

#ifdef QUEST_CHARSET_UNICODE
#ifdef QUEST_COMPILER_MSVC
typedef wchar_t vchar;
#else
typedef u16 vchar;
#endif
#define _V(string) L ## string
#define V(string) _V(string)
#define Vforcechar(x, y) wcstombs(x, y, Vstrlen(y))
#define Vforcevcharfromchar(x, y) mbstowcs(x, y, strlen(y))
#define Vsprintfu swprintf
#define Vprintf wprintf
#define Vsprintf swprintf_s
#define Vstrcmp wcscmp
#define Vstrcat wcscat_s
#define Vstrcatu wcscat
#define Vstrtok(x, y) wcstok(x, y, NULL)
#define Vstrdup wcsdup
#define Vstrstr wcsstr
#define Vtolower towlower
#define Vfopen _wfopen
#define Vvsprintf vswprintf
#define Vsnprintf _snwprintf
#define Vvsnprintf _vsnwprintf
#define Vstrftime wcsftime
#define Vstrcopy wcsncpy
#define Vfgets fgetws
//#define Vstrsep wcstok_r
#else
typedef u8 vchar;
#define V(string) string
#define Vforcechar(x, y) y = x
#define Vforcevcharfromchar(x, y) y = x
#define Vsprintfu sprintf
#define Vprintf printf
#define Vsprintf sprintf_s
#define Vstrcmp strcmp
#define Vstrcat strcat_s
#define Vstrcatu strcat
#define Vstrtok strtok
#define Vstrdup strdup_s
#define Vstrstr strstr
//#define Vstrsep strsep
#define Vsnprintf snprintf
#define Vvsnprintf vsnprintf
#define Vtolower tolower
#define Vfopen fopen
#define Vvsprintf vsprintf
#define Vstrftime strftime
#define Vstrcopy strncpy
#define Vfgets fgets
#endif

#define Vconstcopy(x) \
  usize strSize = (Vstrlen( x ) + 1) * sizeof(vchar); \
  vchar* x##Owned = (vchar*) conjure(strSize); \
  copyMemory( x, x##Owned, strSize);


forceinline usize Vstrlen(const vchar* a)
{
	usize length = 0;
	while ((*a) != V('\0'))
	{
		length++;
		a++;
	}

	return(length);
}

forceinline b8 Vstrequal(const vchar* a, const vchar* b)
{
	vchar* ourA = (vchar*)a;
	vchar* ourB = (vchar*)b;
	do
	{
		if ((*ourA) != (*ourB))
			return(false);
		ourA++;
		ourB++;
	} while ((*ourA) != V('\0'));

	return(true);
}

#endif
