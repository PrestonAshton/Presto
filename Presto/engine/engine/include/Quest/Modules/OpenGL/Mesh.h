#ifndef QUEST_MODULES_OPENGL_MESH_H
#define QUEST_MODULES_OPENGL_MESH_H

#include <Quest/Common.h>
#include <Quest/Graphics/MeshData.h>
#include <Quest/Modules/OpenGL/Functions.h>

typedef struct
{
	GLuint vbo;
	GLuint ibo;
	GLsizei drawCount;
} GLMesh;

DEFINE_HASHMAP(GLMesh);

extern Hashmap_GLMesh g_glMeshes;

GLMesh GLMeshGenerateMesh(MeshData* data);
void GLMeshAddMesh(u64 name, MeshData* data);

forceinline void GLMeshDraw(GLMesh mesh)
{
	GL_FUNCTION(glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo));
	GL_FUNCTION(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ibo));

	GL_FUNCTION(glVertexAttribPointer((GLuint)(Position), (GLint)(3), GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(0)));
	GL_FUNCTION(glVertexAttribPointer((GLuint)(TexCoord), (GLint)(2), GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(sizeof(Vector3))));
	GL_FUNCTION(glVertexAttribPointer((GLuint)(Colour), (GLint)(4), GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (const GLvoid*)(sizeof(Vector3) + sizeof(Vector2))));
	GL_FUNCTION(glVertexAttribPointer((GLuint)(Normal), (GLint)(3), GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(sizeof(Vector3) + sizeof(Vector2) + sizeof(Colour32))));
	GL_FUNCTION(glVertexAttribPointer((GLuint)(Tangent), (GLint)(3), GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(sizeof(Vector3) + sizeof(Vector2) + sizeof(Colour32) + sizeof(Vector3))));

	GL_FUNCTION(glDrawElements(GL_TRIANGLES, (GLsizei)mesh.drawCount, GL_UNSIGNED_INT, NULL));
}

#endif