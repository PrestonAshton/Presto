#ifndef QUEST_MODULES_OPENGL_SHARED_TEXTURE_H
#define QUEST_MODULES_OPENGL_SHARED_TEXTURE_H

#include <Quest/Common.h>
#include <Quest/Graphics/Colour.h>
#include <Quest/Modules/OpenGL/Mesh.h>

/*enum TextureFilter
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
};*/

typedef struct
{
	u16 object;
} GLTexture;

// <-- Texture | 64 bits | 8 bytes -->
// Test this.
STATIC_ASSERT(sizeof(GLTexture) == 2, Size_Of_GLTexture);

DEFINE_HASHMAP(GLTexture);

Hashmap_GLTexture g_glTextures = { 0 };

GLTexture GLTextureLoadFromFile(const a8* path);
GLTexture GLTextureLoadFromImage(Image image);

void GLTextureAddFromFile(const a8* path);
void GLTextureAddFromData(u64 name, Image image);

forceinline void GLTextureBindTexture(GLTexture texture, u8 position)
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
