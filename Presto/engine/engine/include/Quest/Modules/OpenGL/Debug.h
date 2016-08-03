#ifndef QUEST_MODULES_OPENGL_DEBUG_H
#define QUEST_MODULES_OPENGL_DEBUG_H

void GLDebugCheckErrors(void);

#ifdef _DEBUG
#define GL_FUNCTION(x) x; GLDebugCheckErrors()
#else
#define GL_FUNCTION(x) x
#endif

#endif