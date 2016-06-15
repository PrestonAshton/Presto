#ifndef QUEST_GRAPHICS_DIMENSIONS_H
#define QUEST_GRAPHICS_DIMENSIONS_H

#inlude <Quest/Common.h>

typedef struct
{
  u32 width;
  u32 height;
} Dimensions;

forceinline f32 DimensionsGetAspectRatio(Dimensions dimensions)
{
  if (dimensions.width == 0 || dimensions.height == 0)
    return(1.0f);

  return(dimensions.width / dimensions.height);
}

#endif
