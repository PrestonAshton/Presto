#ifndef PSTDLIB_MATH_CONSTANTS_H
#define PSTDLIB_MATH_CONSTANTS_H

#include <Presto/Common/Types.h>

typedef struct
{
  f32 Epsilon;
  f32 Third;
  f32 TwoThirds;
  f32 E;
  f32 Pi;
  f32 Tau;
  f32 Sqrt2;
  f32 Sqrt3;
  f32 Sqrt5;
  f32 GoldenRatio;
} __constants32__;

typedef struct
{
  f64 Epsilon;
  f64 Third;
  f64 TwoThirds;
  f64 E;
  f64 Pi;
  f64 Tau;
  f64 Sqrt2;
  f64 Sqrt3;
  f64 Sqrt5;
  f64 GoldenRatio;
} __constants64__;

PSTDLIB_EXPORT extern __constants32__ Constants32;
PSTDLIB_EXPORT extern __constants64__ Constants64;

#endif
