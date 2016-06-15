#ifndef QUEST_GRAPHICS_OPENGL_H
#define QUEST_GRAPHICS_OPENGL_H

extern PROC(*DwglGetProcAddress)(LPCSTR name);
#define wglGetProcAddress DwglGetProcAddress

#include <Quest/Graphics/OpenGL/OpenGLGen.h>
#include <Quest/Graphics/OpenGL/GLRenderPath.h>
#include <Quest/Graphics/OpenGL/Shaders.h>

#endif
