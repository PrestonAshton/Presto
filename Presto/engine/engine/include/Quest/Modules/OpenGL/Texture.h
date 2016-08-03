#ifndef QUEST_MODULES_OPENGL_SHARED_TEXTURE_H
#define QUEST_MODULES_OPENGL_SHARED_TEXTURE_H

#include <Quest/Common.h>
#include <Quest/Graphics/Colour.h>
#include <Quest/Modules/OpenGL/Debug.h>
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
	GLuint object;
} GLTexture;

DEFINE_HASHMAP(GLTexture);

extern Hashmap_GLTexture g_glTextures;

GLTexture GLTextureLoadFromFile(const a8* path);
GLTexture GLTextureLoadFromImage(Image image);

void GLTextureAddFromFile(const a8* path);
void GLTextureAddFromData(u64 name, Image image);

forceinline void GLTextureBindTexture(GLTexture texture, u8 position)
{
	if (position > 31)
		position = 31;

	GL_FUNCTION(glActiveTexture(GL_TEXTURE0 + position));

	GL_FUNCTION(glEnable(GL_TEXTURE_2D));
	GL_FUNCTION(glBindTexture(GL_TEXTURE_2D, texture.object));
	GL_FUNCTION(glDisable(GL_TEXTURE_2D));
}

#endif
