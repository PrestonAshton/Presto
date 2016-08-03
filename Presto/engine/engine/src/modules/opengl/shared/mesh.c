Hashmap_GLMesh g_glMeshes = { 0 };

GLMesh GLMeshGenerateMesh(MeshData* data)
{
	GLMesh mesh = { 0 };

	GL_FUNCTION(glGenBuffers(1, &(mesh.vbo)));
	GL_FUNCTION(glGenBuffers(1, &(mesh.ibo)));

	mesh.drawCount = data->indices.length;

	GL_FUNCTION(glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo));
	GL_FUNCTION(glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * data->vertices.length, &(data->vertices.data[0]), GL_STATIC_DRAW));

	GL_FUNCTION(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ibo));
	GL_FUNCTION(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32) * data->indices.length, &(data->indices.data[0]), GL_STATIC_DRAW));

	return mesh;
}

void GLMeshAddMesh(u64 name, MeshData* data)
{
	GLMesh mesh = GLMeshGenerateMesh(data);
	Hashmap_GLMeshSetByValue(&g_glMeshes, name, mesh);
}
