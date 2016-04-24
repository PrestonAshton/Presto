#ifndef PRESTO_COMMON_COMPILERS_H
#define PRESTO_COMMON_COMPILERS_H

#if   defined(_MSC_VER)
#define PRESTO_COMPILER_MSVC
#elif defined(__clang__)
#define PRESTO_COMPILER_CLANG
#elif defined(__GNUC__) || defined(__GNUG__) && !(defined(__clang__))
#define PRESTO_COMPILER_GNU_GCC
#elif defined(__INTEL_COMPILER)
#define PRESTO_COMPILER_INTEL
#endif

#endif