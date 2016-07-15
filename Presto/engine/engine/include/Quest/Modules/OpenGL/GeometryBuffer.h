#ifndef QUEST_MODULES_OPENGL_SHARED_GEOMETRYBUFFER_H
#define QUEST_MODULES_OPENGL_SHARED_GEOMETRYBUFFER_H

#include <Quest/Common.h>

typedef struct
{
	// Not using normal textures here for size efficiency.
	// This is more efficient in both performance and size in this case.

	u16 diffuse;
	u16 specular;
	u16 normal;
	u16 depth;
	
	// u16 emission;
	// Note: Replace padding with this when the time comes!

	// <-- 64 bits | 8 bytes -->

	u16 width;
	u16 height;
	u16 fbo;
	u16 padding;

	// <-- 64 bits | 8 bytes -->

} GeometryBuffer;

// <-- Geometry Buffer | 128 bits | 16 bytes -->
// Test this.
STATIC_ASSERT(sizeof(GeometryBuffer) == 16, Size_Of_GeometryBuffer);


#endif
