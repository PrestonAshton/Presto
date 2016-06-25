#ifndef QUEST_GRAPHICS_OPENGL_SHADERS_H
#define QUEST_GRAPHICS_OPENGL_SHADERS_H

// SOA not AOS

typedef struct
{
	Array objects;
	Array attribLocations;
	Array uniformLocations;
} OpenGLShaderPrograms;

extern OpenGLShaderPrograms glShaderPrograms;

void InitialiseGLShaderSystems();
#ifdef QUEST
INITIALIZER(InitialiseGLShaderSystems);
#endif

// returns the shader object
forceinline u32 OpenGLCreateShader()
{
	u32 shaderObject = glCreateProgram();
	ArrayPushBack(&glShaderPrograms.objects, &shaderObject);

	Hashmap* shaderAttribArray = spawn(sizeof(Array));
	ArrayPushBack(&glShaderPrograms.attribLocations, &shaderAttribArray);
	//
	Hashmap* shaderUniformArray = spawn(sizeof(Hashmap));
	ArrayPushBack(&glShaderPrograms.uniformLocations, &shaderUniformArray);

	return(0);
}

#endif
