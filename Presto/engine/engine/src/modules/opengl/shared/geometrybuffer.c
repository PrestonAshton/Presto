GLGeometryBuffer g_glGeometryBuffer = { 0 };

forceinline GLAddRenderTarget(u16 width, u16 height, GLuint* object, GLenum attachment, i32 internalFormat, u32 format, u32 type)
{
	if (!*object)
		GL_FUNCTION(glGenTextures(1, object));

	GL_FUNCTION(glBindTexture(GL_TEXTURE_2D, *object));
	GL_FUNCTION(glTexImage2D(GL_TEXTURE_2D, 0, (GLint)internalFormat, (GLsizei)width, (GLsizei)height, 0, (GLenum)format, (GLenum)type, NULL));
	GL_FUNCTION(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GL_FUNCTION(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GL_FUNCTION(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GL_FUNCTION(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

	GL_FUNCTION(glFramebufferTexture(GL_FRAMEBUFFER, attachment, *object, 0));
}

void GLGeometryBufferCreate(u16 width, u16 height)
{
	if (width == g_glGeometryBuffer.width && height == g_glGeometryBuffer.height)
		return;

	g_glGeometryBuffer.width = width;
	g_glGeometryBuffer.height = height;

	if (!g_glGeometryBuffer.fbo)
	{
		GL_FUNCTION(glGenFramebuffers(1, &(g_glGeometryBuffer.fbo)));
	}

	GL_FUNCTION(glBindFramebuffer(GL_FRAMEBUFFER, g_glGeometryBuffer.fbo));

	GLuint depthRenderBuffer;

	GL_FUNCTION(glGenRenderbuffers(1, &depthRenderBuffer));
	GL_FUNCTION(glBindRenderbuffer(GL_RENDERBUFFER, depthRenderBuffer));
	GL_FUNCTION(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, (GLsizei)g_glGeometryBuffer.width, (GLsizei)g_glGeometryBuffer.height));
	GL_FUNCTION(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderBuffer));

	GLuint drawBuffers[3];
	drawBuffers[0] = GL_COLOR_ATTACHMENT0;
	drawBuffers[1] = GL_COLOR_ATTACHMENT1;
	drawBuffers[2] = GL_COLOR_ATTACHMENT2;

	GLAddRenderTarget(width, height, &(g_glGeometryBuffer.diffuse.object), GL_COLOR_ATTACHMENT0, GL_RGB8, GL_RGB, GL_UNSIGNED_BYTE);
	GLAddRenderTarget(width, height, &(g_glGeometryBuffer.specular.object), GL_COLOR_ATTACHMENT1, GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE);
	GLAddRenderTarget(width, height, &(g_glGeometryBuffer.normal.object), GL_COLOR_ATTACHMENT2, GL_RGB10_A2, GL_RGBA, GL_FLOAT);
	GLAddRenderTarget(width, height, &(g_glGeometryBuffer.depth.object), GL_DEPTH_ATTACHMENT, GL_DEPTH_COMPONENT24, GL_DEPTH_COMPONENT, GL_FLOAT);

	GL_FUNCTION(glDrawBuffers(3, &drawBuffers[0]));
	GL_FUNCTION(glBindTexture(GL_TEXTURE_2D, 0));
	GL_FUNCTION(glBindFramebuffer(GL_FRAMEBUFFER, 0));

#ifdef _DEBUG
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		FAIL("Framebuffer incomplete!");
	}
#endif
}