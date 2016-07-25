#ifndef QUEST_MODULES_OPENGL_MATERIAL_H
#define QUEST_MODULES_OPENGL_MATERIAL_H

#include <Quest/Common.h>
#include <Quest/Graphics/Colour.h>
#include <Quest/Modules/OpenGL/Texture.h>

typedef struct
{
	GLTexture diffuseMap;
	GLTexture normalMap;

	Colour32 diffuseColour;
	f32 specularExponent;
} GLMaterial;

DEFINE_HASHMAP(GLMaterial);

extern Hashmap_GLMaterial g_glMaterials;

void GLMaterialAddFromData (const u64 name, const u64 diffuseName, const u64 normalName, Colour32 colour, f32 specularExponent);

#endif