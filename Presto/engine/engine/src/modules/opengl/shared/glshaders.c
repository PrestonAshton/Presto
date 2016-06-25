OpenGLShaderPrograms glShaderPrograms = { 0 };

void InitialiseGLShaderSystems()
{
	glShaderPrograms.objects = ArrayCreate(u32);
	glShaderPrograms.attribLocations = ArrayCreate(Array*);
	glShaderPrograms.uniformLocations = ArrayCreate(Array*);
}
