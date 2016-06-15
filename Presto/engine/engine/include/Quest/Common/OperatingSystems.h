#ifndef QUEST_COMMON_OPERATINGSYSTEMS_H
#define QUEST_COMMON_OPERATINGSYSTEMS_H

#if defined(_WIN32) || defined (_WIN64) || defined (__WIN32) || defined (__WIN64) || defined (WIN32) || defined (WIN64)
#define QUEST_SYSTEM_WINDOWS
#elif defined (__APPLE__) && defined(__MACH__)
#define QUEST_SYSTEM_OSX
#define QUEST_SYSTEM_UNIX
#elif defined (__unix__)
#define QUEST_SYSTEM_UNIX
#if defined (__linux__)
#define QUEST_SYSTEM_LINUX
#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
#define QUEST_SYSTEM_FREEBSD
#else
#define QUEST_SYSTEM_OTHER_UNIX
#endif
#else
#endif

#endif