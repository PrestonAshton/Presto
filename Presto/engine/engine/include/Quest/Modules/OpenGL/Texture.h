#ifndef QUEST_MODULES_OPENGL_SHARED_TEXTURE_H
#define QUEST_MODULES_OPENGL_SHARED_TEXTURE_H

#include <Quest/Common.h>

enum TextureFilter
{
	Linear,
	Nearest,
};

enum TextureWrapMode
{
	Clamp,
	Repeat,
	ClampToEdge,
	ClampToBorder,
	MirroredRepeat
};

typedef struct
{
	u16 object;
	u16 width;
	u16 height;
	u16 padding;
} Texture;

// <-- Texture | 64 bits | 8 bytes -->
// Test this.
STATIC_ASSERT(sizeof(Texture) == 8, Size_Of_Texture);

forceinline void BindTexture(Texture texture, u8 position)
{
	if (position > 31)
		position = 31;

	// TODO: Do we need? glEnable(GL_TEXTURE_2D)

	glActiveTexture(GL_TEXTURE0 + position);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture.object);
	glDisable(GL_TEXTURE_2D);
}


#endif
