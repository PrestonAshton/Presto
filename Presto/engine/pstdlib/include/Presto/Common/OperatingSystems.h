#ifndef PRESTO_COMMON_OPERATINGSYSTEMS_H
#define PRESTO_COMMON_OPERATINGSYSTEMS_H

#if defined(_WIN32) || defined (_WIN64) || defined (__WIN32) || defined (__WIN64) || defined (WIN32) || defined (WIN64)
#define PRESTO_SYSTEM_WINDOWS
#elif defined (__APPLE__) && defined(__MACH__)
#define PRESTO_SYSTEM_OSX
#define PRESTO_SYSTEM_UNIX
#elif defined (__unix__)
#define PRESTO_SYSTEM_UNIX
#if defined (__linux__)
#define PRESTO_SYSTEM_LINUX
#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
#define PRESTO_SYSTEM_FREEBSD
#else
#define PRESTO_SYSTEM_OTHER_UNIX
#endif
#else
#endif

#endif