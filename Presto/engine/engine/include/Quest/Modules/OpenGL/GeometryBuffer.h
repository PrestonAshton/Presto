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

	u32 width;
	u32 height;
	GLuint fbo;
} GLGeometryBuffer;

extern GLGeometryBuffer g_glGeometryBuffer;

void GLGeometryBufferCreate(u16 width, u16 height);

forceinline void GLGeometryBufferBind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, g_glGeometryBuffer.fbo);
}

forceinline void GLGeometryBufferUnbind()
{
	glFlush();
	glBindFramebuffer(GL_FRAMEBUFFER, NULL);
}


#endif
