#ifndef QUEST_GRAPHICS_LIGHTING_H
#define QUEST_GRAPHICS_LIGHTING_H

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
  Attenuation attenuation
  f32 range;
  BaseLight base;
} PointLight;

forceinline void PointLightCalculateRange(const PointLight* light)
{
  f32 i = brightness * (f32)max(light->base->colour.r, max(light->base->colour.g, light->base->colour.b));

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

forceinline void SpotLightCalculateRange(const SpotLight* light)
{
  PointLightCalculateRange(light->base);
}

#endif
