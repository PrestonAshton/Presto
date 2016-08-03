a8* GLLoadShaderFile(const a8* path)
{
	String output = { 0 };

	a8* contents = ReadEntireTextFile(path);

	if (!contents)
		return "";

	a8* line = strtok(contents, "\n");
	a8* includeMarker = NULL;
	while (line != NULL)
	{
		if (strstr(line, "#include"))
		{
			String lineStr = { 0 };
			StrAppendCStr(&lineStr, line);

			String fileName = { 0 };
			StrAppendCStr(&fileName, "shaders/");
			String includeFile = StrSubstring(&lineStr, 10, StrLength(&lineStr) - 1);
			StrAppendStr(&fileName, &includeFile);

			a8* file = ReadEntireTextFile(StrCStr(&fileName));
			StrAppendCStr(&output, file);
			murder(fileName.data.data);
			murder(includeFile.data.data);
			murder(lineStr.data.data);
		}
		else
		{
			StrAppendCStr(&output, line);
		}
		StrAppendCStr(&output, "\n");
		line = strtok(NULL, "\n");
	}

	murder(contents);
	return StrCStr(&output);
}

b8 GLAttachShaderFromMemory(a8* source, GLuint type, GLuint object)
{
	GLuint shader = 0;
	shader = glCreateShader(type);

	GL_FUNCTION(glShaderSource(shader, 1, &source, NULL));
	GL_FUNCTION(glCompileShader(shader));

	GLint status = 0;
	GL_FUNCTION(glGetShaderiv(shader, GL_COMPILE_STATUS, &status));

	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		GL_FUNCTION(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength));

		a8* infoLog = conjure(infoLogLength + 1);
		GL_FUNCTION(glGetShaderInfoLog(shader, infoLogLength, NULL, infoLog));
		infoLog[infoLogLength] = '\0';

		vchar* buffer = conjure((infoLogLength + 1) * sizeof(vchar));

		Vforcevcharfromchar(buffer, infoLog);
		FAIL(V("Shader failed to compile! OpenGL log: \n%s"), buffer);

		GL_FUNCTION(glDeleteShader(shader));
		return false;
	}

	GL_FUNCTION(glAttachShader(object, shader));
	return true;
}

void GLLinkShader(GLuint object)
{
	GL_FUNCTION(glLinkProgram(object));

	GLint status = 0;
	GL_FUNCTION(glGetProgramiv(object, GL_LINK_STATUS, &status));

	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		GL_FUNCTION(glGetProgramiv(object, GL_INFO_LOG_LENGTH, &infoLogLength));

		a8* infoLog = conjure(infoLogLength + 1);
		GL_FUNCTION(glGetProgramInfoLog(object, infoLogLength, NULL, infoLog));
		infoLog[infoLogLength] = '\0';

		vchar* buffer = conjure((infoLogLength + 1) * sizeof(vchar));

		Vforcevcharfromchar(buffer, infoLog);
		FAIL(V("Shader failed to link! OpenGL log: \n%s"), buffer);

		GL_FUNCTION(glDeleteProgram(object));
		return false;
	}

	return true;
}

// returns the shader object
void GLCreateShader(const a8* vertexPath, const a8* fragmentPath, u32 shaderId)
{
	g_glShaderObjects[shaderId] = glCreateProgram();

	a8* vertexShader = GLLoadShaderFile(vertexPath);
	a8* fragmentShader = GLLoadShaderFile(fragmentPath);

	GLAttachShaderFromMemory(vertexShader, GL_VERTEX_SHADER, g_glShaderObjects[shaderId]);
	GLAttachShaderFromMemory(fragmentShader, GL_FRAGMENT_SHADER, g_glShaderObjects[shaderId]);

	glBindAttribLocation((GLuint)g_glShaderObjects[shaderId], (GLuint)Position, (GLchar*)"a_position");
	glBindAttribLocation((GLuint)g_glShaderObjects[shaderId], (GLuint)TexCoord, (GLchar*)"a_texCoord");
	glBindAttribLocation((GLuint)g_glShaderObjects[shaderId], (GLuint)Colour, (GLchar*)"a_colour");
	glBindAttribLocation((GLuint)g_glShaderObjects[shaderId], (GLuint)Normal, (GLchar*)"a_normal");
	glBindAttribLocation((GLuint)g_glShaderObjects[shaderId], (GLuint)Tangent, (GLchar*)"a_tangent");

	GLLinkShader(g_glShaderObjects[shaderId]);

	murder(vertexShader);
	murder(fragmentShader);
}