void GLDebugCheckErrors(void)
{
	u32 error = GL_NO_ERROR;
	while ((error = glGetError()) != GL_NO_ERROR)
	{
		const vchar* errorMessage = V("Unknown Error!");
		switch (error)
		{
		case GL_INVALID_ENUM: errorMessage = V("GL_INVALID_ENUM"); break;
		case GL_INVALID_VALUE: errorMessage = V("GL_INVALID_VALUE"); break;
		case GL_INVALID_OPERATION: errorMessage = V("GL_INVALID_OPERATION"); break;
		case 0x0503: errorMessage = V("GL_STACK_OVERFLOW"); break;
		case 0x0504: errorMessage = V("GL_STACK_UNDERFLOW"); break;
		case GL_OUT_OF_MEMORY: errorMessage = V("GL_OUT_OF_MEMORY"); break;
		case GL_INVALID_FRAMEBUFFER_OPERATION: errorMessage = V("GL_INVALID_FRAMEBUFFER_OPERATION"); break;
		case 0x0507: errorMessage = V("GL_CONTEXT_LOST"); break;
		case 0x8031: errorMessage = V("GL_TABLE_TOO_LARGE1"); break;
		}
		FAIL(V("OpenGL error! Name: %s | Hex: 0x%x | Dec: %d"), errorMessage, error, error);
	}
}
