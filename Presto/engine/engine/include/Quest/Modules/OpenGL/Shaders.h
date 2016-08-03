#ifndef QUEST_GRAPHICS_OPENGL_SHADERS_H
#define QUEST_GRAPHICS_OPENGL_SHADERS_H

#include <Quest/Utility/Filesystem.h>
#include <Quest/Graphics/MeshData.h>

enum UsedShaders
{
	GLGeometryPass = 0,
	GLSpotLightPass = 1,
	GLAmbientLightPass = 2,
	GLPointLightPass,
	GLDirectionalLightPass,
	GLOutput,
	GLTargetPassThru,
	GLTotalShaders
};

void GLCreateShader(const a8* vertexPath, const a8* fragmentPath, GLuint shaderId);

GLuint g_glShaderObjects[GLTotalShaders] = { 0 };

// u_camera
// u_cameraPosition

// u_material.diffuseMap
// u_material.normalMap
// u_material.diffuseColour
// u_material.specularColour
// u_material.specularExponent

// u_transform.position
// u_transform.orientation
// u_transform.scale

// u_diffuse
// u_lighting
// u_gamma
// u_tex
// u_specular
// u_normal
// u_depth
// u_cameraInverse

// u_light.intensities
// u_light.position
// u_light.base.intensities
// u_light.attenuation.constant
// u_light.attenuation.linear
// u_light.attenuation.quadratic
// u_light.range
// u_light.direction
// u_light.coneAngle

typedef struct
{
	GLuint u_camera;
	GLuint u_cameraPosition;

	struct
	{
		GLuint diffuseMap;
		GLuint normalMap;
		GLuint diffuseColour;
		GLuint specularColour;
		GLuint specularExponent;
	} u_material;

	struct
	{
		GLuint position;
		GLuint orientation;
		GLuint scale;
	} u_transform;

	GLuint u_diffuse;
	GLuint u_lighting;
	GLuint u_gamma;
	GLuint u_tex;
	GLuint u_specular;
	GLuint u_normal;
	GLuint u_depth;
	GLuint u_cameraInverse;

	struct
	{
		GLuint intensities;
		GLuint position;
		struct
		{
			GLuint intensities;
		} base;
		struct
		{
			GLuint constant;
			GLuint linear;
			GLuint quadratic;
		} attenuation;

		GLuint range;
		GLuint direction;
		GLuint coneAngle;
	} u_light;
} GLUniformSet;


GLUniformSet g_glUniformPositions[GLTotalShaders] = { 0 };

#define GET_UNIFORM(shader, uniform) g_glUniformPositions[ shader ].##uniform

#define REGISTER_UNIFORM(shader, uniform) GET_UNIFORM(shader, uniform) = glGetUniformLocation(g_glShaderObjects[shader], #uniform )

#endif
