#ifndef PSTDLIB_MATH_ANGLE_H
#define PSTDLIB_MATH_ANGLE_H

#include <Presto/Math/Constants.h>

typedef f32 Radian;
typedef f32 Degree;

forceinline Degree RadianToDegree(Radian radians)
{
  return(360.0f * radians / Constants32.Tau);
}

forceinline Radian DegreeToRadian(Degree degrees)
{
  return(degrees * Constants32.Tau / 360.0f);
}

#endif
