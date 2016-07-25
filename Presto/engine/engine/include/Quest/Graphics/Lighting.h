#ifndef QUEST_GRAPHICS_LIGHTING_H
#define QUEST_GRAPHICS_LIGHTING_H


#include <Quest/Containers.h>

typedef struct
{
	f32 constant;
	f32 linear;
	f32 quadratic;
} Attenuation;

typedef struct
{
	f32 brightness;
	Colour24 colour;
} BaseLight;

typedef struct
{
	BaseLight base;
	Vector3 direction;
} DirectionalLight;

typedef struct
{
	Vector3 position;
	Attenuation attenuation;
	f32 range;
	BaseLight base;
} PointLight;

DEFINE_ARRAY(BaseLight);
DEFINE_ARRAY(DirectionalLight);
DEFINE_ARRAY(PointLight);

forceinline void PointLightCalculateRange(PointLight* light)
{
	f32 i = light->base.brightness * (f32)MAX(light->base.colour.r, MAX(light->base.colour.g, light->base.colour.b));

	f32 r = -light->attenuation.linear +
		sqrtf(light->attenuation.linear * light->attenuation.linear - 4.0f * light->attenuation.quadratic * (light->attenuation.constant - i));
	r /= 2.0f * light->attenuation.quadratic;

	light->range = r;
}

typedef struct
{
	Radian coneAngle;
	Vector3 direction;

	PointLight base;
} SpotLight;

DEFINE_ARRAY(SpotLight);

forceinline void SpotLightCalculateRange(SpotLight* light)
{
	PointLightCalculateRange(&(light->base));
}

#endif
