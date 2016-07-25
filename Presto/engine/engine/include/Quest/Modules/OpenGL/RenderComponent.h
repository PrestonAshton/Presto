#ifndef QUEST_MODULES_OPENGL_RENDERCOMPONENT_H
#define QUEST_MODULES_OPENGL_RENDERCOMPONENT_H

#include <Quest/Modules/OpenGL/Material.h>
#include <Quest/Modules/OpenGL/Mesh.h>

typedef struct
{
	GLMaterial material;
	GLMesh mesh;
} GLRenderComponent;

#endif