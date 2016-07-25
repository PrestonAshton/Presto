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

b8 GLAttachShaderFromMemory(a8* source, u16 type, u8 object)
{
	u8 shader = 0;
	shader = glCreateShader(type);

	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	i32 status = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE)
	{
		i32 infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

		a8* infoLog = conjure(infoLogLength + 1);
		glGetShaderInfoLog(shader, infoLogLength, NULL, infoLog);
		infoLog[infoLogLength] = '\0';

		vchar* buffer = conjure((infoLogLength + 1) * sizeof(vchar));

		Vforcevcharfromchar(buffer, infoLog);
		FAIL(V("Shader failed to compile! OpenGL log: \n%s"), buffer);

		glDeleteShader(shader);
		return false;
	}

	glAttachShader(object, shader);
	return true;
}

void GLLinkShader(u8 object)
{
	glLinkProgram(object);

	i32 status = 0;
	glGetProgramiv(object, GL_LINK_STATUS, &status);

	if (status == GL_FALSE)
	{
		i32 infoLogLength;
		glGetProgramiv(object, GL_INFO_LOG_LENGTH, &infoLogLength);

		a8* infoLog = conjure(infoLogLength + 1);
		glGetProgramInfoLog(object, infoLogLength, NULL, infoLog);
		infoLog[infoLogLength] = '\0';

		vchar* buffer = conjure((infoLogLength + 1) * sizeof(vchar));

		Vforcevcharfromchar(buffer, infoLog);
		FAIL(V("Shader failed to link! OpenGL log: \n%s"), buffer);

		glDeleteProgram(object);
		return false;
	}

	return true;
}

// returns the shader object
void GLCreateShader(const a8* vertexPath, const a8* fragmentPath, u8 shaderId)
{
	g_glShaderObjects[shaderId] = glCreateProgram();

	a8* vertexShader = GLLoadShaderFile(vertexPath);
	a8* fragmentShader = GLLoadShaderFile(fragmentPath);

	GLAttachShaderFromMemory(vertexShader, GL_VERTEX_SHADER, g_glShaderObjects[shaderId]);
	GLAttachShaderFromMemory(fragmentShader, GL_FRAGMENT_SHADER, g_glShaderObjects[shaderId]);

	GLLinkShader(g_glShaderObjects[shaderId]);

	murder(vertexShader);
	murder(fragmentShader);
}

forceinline void GLRegisterUniform(u8 uniformPosition, u8 shaderId, const a8* name)
{
	GET_UNIFORM(shaderId, uniformPosition) = glGetUniformLocation(g_glShaderObjects[shaderId], name);
}