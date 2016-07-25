#ifndef QUEST_GRAPHICS_MESH_H
#define QUEST_GRAPHICS_MESH_H

#include <Quest/Common.h>
#include <Quest/Graphics/Vertex.h>

typedef enum
{
	Position = 0,
	TexCoord = 1,
	Colour = 2,
	Normal = 3,
	Tangent = 4
} AttribLocation;


typedef struct
{
	Array_Vertex vertices;
	Array_u32 indices;
} MeshData;

void MeshDataGenerateNormals(MeshData* data);

forceinline void MeshDataAddFace(MeshData* data, u32 a, u32 b, u32 c)
{
	Array_u32PushBack(&(data->indices), a);
	Array_u32PushBack(&(data->indices), b);
	Array_u32PushBack(&(data->indices), c);
}
forceinline void MeshDataAddFaceOffset(MeshData* data, u32 offset, u32 a, u32 b, u32 c)
{
	Array_u32PushBack(&(data->indices), offset + a);
	Array_u32PushBack(&(data->indices), offset + b);
	Array_u32PushBack(&(data->indices), offset + c);
}

#endif