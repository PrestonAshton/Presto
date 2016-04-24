#ifndef PRESTO_COMMON_TYPES_H
#define PRESTO_COMMON_TYPES_H

#include <Presto/Common/Charsets.h>
#include <Presto/Common/Architectures.h>
#include <stdio.h>

typedef char a8;
typedef short a16;
typedef long a32;
typedef long long a64;

typedef wchar_t wchar;

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

#if !PRESTO_MAXINT_BITS
#elif PRESTO_MAXINT_BITS == 64
typedef u64 usize;
typedef i64 isize;
#elif PRESTO_MAXINT_BITS == 32
typedef u32 usize;
typedef i32 isize;
#elif PRESTO_MAXINT_BITS == 16
typedef u16 usize;
typedef i16 isize;
#elif PRESTO_MAXINT_BITS == 8
typedef u8 usize;
typedef i8 isize;
#endif

typedef isize iptr;
typedef usize uptr;

typedef i8 b8;
typedef b8 bool;

#endif