#ifndef QUEST_MODULES_OPENGL_MESH_H
#define QUEST_MODULES_OPENGL_MESH_H

#include <Quest/Common.h>
#include <Quest/Graphics/MeshData.h>
#include <Quest/Modules/OpenGL/Functions.h>

typedef struct
{
	u32 vbo;
	u32 ibo;
	u64 drawCount;
} GLMesh;

DEFINE_HASHMAP(GLMesh);

extern Hashmap_GLMesh g_glMeshes;

GLMesh GLMeshGenerateMesh(MeshData* data);
void GLMeshAddMesh(u64 name, MeshData* data);

forceinline void GLMeshDraw(GLMesh mesh)
{
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ibo);

	glVertexAttribPointer(Position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(0));
	glVertexAttribPointer(TexCoord, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(sizeof(Vector3)));
	glVertexAttribPointer(Colour, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (const GLvoid*)(sizeof(Vector3) + sizeof(Vector2)));
	glVertexAttribPointer(Normal, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(sizeof(Vector3) + sizeof(Vector2) + sizeof(Colour32)));
	glVertexAttribPointer(Tangent, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(sizeof(Vector3) + sizeof(Vector2) + sizeof(Colour32) + sizeof(Vector3)));

	glDrawElements(GL_TRIANGLES, mesh.drawCount, GL_UNSIGNED_INT, NULL);
}

#endif