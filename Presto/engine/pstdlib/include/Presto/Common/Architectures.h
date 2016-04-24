#ifndef PRESTO_COMMON_ARCHITECTURES_H
#define PRESTO_COMMON_ARCHITECTURES_H

#if defined(_WIN64) || defined (__x86_64__) || defined(__ppc64__) || defined(__WIN64) ||  defined(WIN64)
#define PRESTO_ARCHITECTURE_X64
#define PRESTO_BITSTRING "bin64"
#define PRESTO_MAXINT_BITS 64
#define PRESTO_MAXINT_BYTES 8
#elif __arm__
#define PRESTO_ARCHITECTURE_ARM
#define PRESTO_BITSTRING "binarm"
#define PRESTO_MAXINT_BITS 32
#define PRESTO_MAXINT_BYTES 4
	#warning Presto may not work on this platform, no tests have been performed.
#else
#define PRESTO_ARCHITECTURE_X32
#define PRESTO_BITSTRING "bin32"
#define PRESTO_MAXINT_BITS 32
#define PRESTO_MAXINT_BYTES 4
#endif

#endif
