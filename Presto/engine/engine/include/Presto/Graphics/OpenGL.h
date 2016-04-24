#ifndef PRESTO_GRAPHICS_OPENGL_H
#define PRESTO_GRAPHICS_OPENGL_H

extern PROC(*DwglGetProcAddress)(LPCSTR name);
#define wglGetProcAddress DwglGetProcAddress

#include <Presto/Graphics/OpenGLGen.h>
#include <Presto/Graphics/GLRenderPath.h>

#endif
