void MeshDataGenerateNormals(MeshData* data)
{
	for (u32 i = 0; i < data->indices.length; i += 3)
	{
		Vertex* v0 = &(data->vertices.data[data->indices.data[i + 0]]);
		Vertex* v1 = &(data->vertices.data[data->indices.data[i + 0]]);
		Vertex* v2 = &(data->vertices.data[data->indices.data[i + 0]]);

		Vector3 pos0 = Vector3Minus(&(v1->position), &(v0->position));
		Vector3 pos1 = Vector3Minus(&(v2->position), &(v1->position));

		Vector2 st0 = Vector2Minus(&(v1->texCoord), &(v0->texCoord));
		Vector2 st1 = Vector2Minus(&(v2->texCoord), &(v1->texCoord));

		Vector3 crossed = Vector3Cross(&pos0, &pos1);
		Vector3 normal = Vector3Normalise(&crossed);

		f32 length = 1.0f / (st0.x * st1.y - st0.y * st1.x);

		// here Pos0 becomes the tangent.

		Vector3ScaleEquals(&pos0, st1.y);
		Vector3ScaleEquals(&pos1, st1.y);
		Vector3MultiplyEquals(&pos0, &pos1);
		Vector3ScaleEquals(&pos0, length);
		Vector3Normalise(&pos0);

		Vector3AddEquals(&(v0->normal), &normal);
		Vector3AddEquals(&(v0->tangent), &pos0);
		Vector3AddEquals(&(v1->normal), &normal);
		Vector3AddEquals(&(v1->tangent), &pos0);
		Vector3AddEquals(&(v2->normal), &normal);
		Vector3AddEquals(&(v2->tangent), &pos0);
	}

	for (u32 i = 0; i < data->vertices.length; i++)
	{
		Vector3NormaliseEquals(&(data->vertices.data[i].normal));
		Vector3NormaliseEquals(&(data->vertices.data[i].tangent));
	}
}