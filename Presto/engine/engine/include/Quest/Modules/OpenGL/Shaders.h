#ifndef QUEST_GRAPHICS_OPENGL_SHADERS_H
#define QUEST_GRAPHICS_OPENGL_SHADERS_H

#include <Quest/Utility/Filesystem.h>

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

void GLCreateShader(const a8* vertexPath, const a8* fragmentPath, u8 shaderId);
void GLRegisterUniform(u8 uniformPosition, u8 shaderId, const a8* name);

u32 g_glShaderObjects[GLTotalShaders] = { 0 };

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

enum GLUniformPositions
{
	u_camera = 1,
	u_cameraPosition = 2,

	u_material_diffuseMap,
	u_material_normalMap,
	u_material_diffuseColour,
	u_material_specularColour,
	u_material_specularExponent,

	u_transform_position,
	u_transform_orientation,
	u_transform_scale,

	u_diffuse,
	u_lighting,
	u_gamma,
	u_tex,
	u_specular,
	u_normal,
	u_depth,
	u_cameraInverse,

	u_light_intensities,
	u_light_position,
	u_light_base_intensities,
	u_light_attenuation_constant,
	u_light_attenuation_linear,
	u_light_attenuation_quadratic,
	u_light_range,
	u_light_direction,
	u_light_coneAngle,
	TotalUniforms
};


u32 g_glUniformPositions[GLTotalShaders * TotalUniforms] = { 0 };

#define GET_UNIFORM(shader, uniformname) g_glUniformPositions[ ((shader + 1) * TotalUniforms) - uniformname - 1]

#endif
