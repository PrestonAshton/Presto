#ifndef QUEST_COMMON_ARCHITECTURES_H
#define QUEST_COMMON_ARCHITECTURES_H

#if defined(_WIN64) || defined (__x86_64__) || defined(__ppc64__) || defined(__WIN64) ||  defined(WIN64)
#define QUEST_ARCHITECTURE_X64
#define QUEST_BITSTRING "bin64"
#define QUEST_MAXINT_BITS 64
#define QUEST_MAXINT_BYTES 8
#elif __arm__
#define QUEST_ARCHITECTURE_ARM
#define QUEST_BITSTRING "binarm"
#define QUEST_MAXINT_BITS 32
#define QUEST_MAXINT_BYTES 4
	#warning Quest may not work on this platform, no tests have been performed.
#else
#define QUEST_ARCHITECTURE_X32
#define QUEST_BITSTRING "bin32"
#define QUEST_MAXINT_BITS 32
#define QUEST_MAXINT_BYTES 4
#endif

#endif
