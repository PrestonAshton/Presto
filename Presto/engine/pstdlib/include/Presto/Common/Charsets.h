#ifndef PRESTO_COMMON_CHARSETS_H
#define PRESTO_COMMON_CHARSETS_H

#include <wchar.h>
#include <stdio.h>

#if defined(UNICODE)
#define PRESTO_CHARSET_UNICODE
#else
#define PRESTO_CHARSET_ANSI
#endif

#ifdef PRESTO_CHARSET_UNICODE
typedef wchar_t vchar;
#define _V(string) L ## string
#define V(string) _V(string)
#define Vsprintf swprintf_s
#define Vstrcmp wcscmp
#define Vstrlen wcslen
#define Vstrcat wcscat_s
#define Vstrtok wcstok
#define Vstrdup wcsdup
#define Vstrstr wcsstr
#define Vtolower towlower
//#define Vstrsep wcstok_r
#else
typedef char vchar;
#define V(string) string
#define Vsprintf sprintf_s
#define Vstrcmp strcmp
#define Vstrlen strlen
#define Vstrcat strcat_s
#define Vstrtok strtok
#define Vstrdup strdup_s
#define Vstrstr strstr
//#define Vstrsep strsep
#define Vtolower tolower
#endif

#define Vlowerstr(p) \
	for ( ; *p; ++p) *p = Vtolower(*p);

#define Vconstcopy(x) \
  usize strSize = (Vstrlen( x ) + 1) * sizeof(vchar); \
  vchar* x##Owned = (vchar*) conjure(strSize); \
  memcpy( x##Owned , args, strSize);

#endif
