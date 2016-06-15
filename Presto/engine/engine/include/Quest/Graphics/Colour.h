#ifndef PSTDLIB_GRAPHICS_COLOR_H
#define PSTDLIB_GRAPHICS_COLOR_H

#include <Quest/Common/BasicDefinitions.h>
#include <Quest/Common/Types.h>

#include <Quest/Math/Vector3.h>
#include <Quest/Math/Vector4.h>

typedef union
{
	struct
	{
		u8 r, g, b, a;
	};
	u8 data[4];
} Colour32;

typedef union
{
	struct
	{
		u8 r, g, b;
	};
	u8 data[3];
} Colour24;

// NOTE(Questn): Colour32 can be cast to a Colour24 if we don't need the alpha when we normalise.
// eg. Vector3 lightStuff = NormaliseColour24(((Colour24*)(&ourColour32)));

forceinline Vector4 NormaliseColour32(Colour32* colour)
{
	Vector4 lightIntensities;
	lightIntensities.r = (f32)(colour->r) / 255.0f;
	lightIntensities.g = (f32)(colour->g) / 255.0f;
	lightIntensities.b = (f32)(colour->b) / 255.0f;
	lightIntensities.a = (f32)(colour->a) / 255.0f;

	return(lightIntensities);
}

forceinline Vector3 NormaliseColour24(Colour24* colour)
{
	Vector3 lightIntensities;
	lightIntensities.r = (f32)(colour->r) / 255.0f;
	lightIntensities.g = (f32)(colour->g) / 255.0f;
	lightIntensities.b = (f32)(colour->b) / 255.0f;

	return(lightIntensities);
}


#endif
