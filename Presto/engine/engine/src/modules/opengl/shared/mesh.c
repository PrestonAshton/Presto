Hashmap_GLMesh g_glMeshes = { 0 };

GLMesh GLMeshGenerateMesh(MeshData* data)
{
	GLMesh mesh = { 0 };

	glGenBuffers(1, &(mesh.vbo));
	glGenBuffers(1, &(mesh.ibo));

	mesh.drawCount = data->indices.length;

	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) *data->vertices.length, &(data->vertices.data[0]), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32) *data->indices.length, &(data->indices.data[0]), GL_STATIC_DRAW);

	return mesh;
}

void GLMeshAddMesh(u64 name, MeshData* data)
{
	GLMesh mesh = GLMeshGenerateMesh(data);
	Hashmap_GLMeshSetByValue(&g_glMeshes, name, mesh);
}
