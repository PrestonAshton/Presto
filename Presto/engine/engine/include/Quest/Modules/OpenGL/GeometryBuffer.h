#ifndef QUEST_MODULES_OPENGL_SHARED_GEOMETRYBUFFER_H
#define QUEST_MODULES_OPENGL_SHARED_GEOMETRYBUFFER_H

#include <Quest/Common.h>
#include <Quest/Modules/OpenGL/GeometryBuffer.h>
#include <Quest/Modules/OpenGL/Texture.h>

typedef struct
{
	GLTexture diffuse;
	GLTexture specular;
	GLTexture normal;
	GLTexture depth;

	// u16 emission;
	// Note: Replace padding with this when the time comes!

	// <-- 64 bits | 8 bytes -->

	u16 width;
	u16 height;
	u16 fbo;
	u16 padding;

	// <-- 64 bits | 8 bytes -->

} GLGeometryBuffer;

// <-- Geometry Buffer | 128 bits | 16 bytes -->
// Test this.
STATIC_ASSERT(sizeof(GLGeometryBuffer) == 16, Size_Of_GLGeometryBuffer);

extern GLGeometryBuffer g_glGeometryBuffer;

void GLGeometryBufferCreate(u16 width, u16 height);

forceinline void GLGeometryBufferBind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, &(g_glGeometryBuffer.fbo));
}

forceinline void GLGeometryBufferUnbind()
{
	glFlush();
	glBindFramebuffer(GL_FRAMEBUFFER, NULL);
}


#endif
