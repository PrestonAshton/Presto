GLGeometryBuffer g_glGeometryBuffer;

forceinline GLAddRenderTarget(u32* drawBuffers, u16 width, u16 height, u16* object, u32 attachment, i32 internalFormat, u32 format, u32 type)
{
	if (!*object)
		glGenTextures(1, object);

	glBindTexture(GL_TEXTURE_2D, *object);
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glFramebufferTexture(GL_FRAMEBUFFER, attachment, *object, 0);
}

void GLGeometryBufferCreate(u16 width, u16 height)
{
	if (width == g_glGeometryBuffer.width && height == g_glGeometryBuffer.height)
		return;

	g_glGeometryBuffer.width = width;
	g_glGeometryBuffer.height = height;

	if (!g_glGeometryBuffer.fbo)
		glGenFramebuffers(1, &(g_glGeometryBuffer.fbo));

	glBindFramebuffer(GL_FRAMEBUFFER, g_glGeometryBuffer.fbo);

	u32 depthRenderBuffer;

	glGenRenderbuffers(1, &depthRenderBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthRenderBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, g_glGeometryBuffer.width, g_glGeometryBuffer.height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderBuffer);

	u32 drawBuffers[2];

	GLAddRenderTarget(&drawBuffers, width, height, &(g_glGeometryBuffer.diffuse), GL_COLOR_ATTACHMENT0, GL_RGB8, GL_RGB, GL_UNSIGNED_BYTE);
	drawBuffers[0] = GL_COLOR_ATTACHMENT0;
	GLAddRenderTarget(&drawBuffers, width, height, &(g_glGeometryBuffer.specular), GL_COLOR_ATTACHMENT1, GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE);
	drawBuffers[1] = GL_COLOR_ATTACHMENT1;
	GLAddRenderTarget(&drawBuffers, width, height, &(g_glGeometryBuffer.normal), GL_COLOR_ATTACHMENT2, GL_RGB10_A2, GL_RGBA, GL_FLOAT);
	GLAddRenderTarget(&drawBuffers, width, height, &(g_glGeometryBuffer.depth), GL_DEPTH_ATTACHMENT, GL_DEPTH_COMPONENT24, GL_DEPTH_COMPONENT, GL_FLOAT);

	glDrawBuffers(2, &drawBuffers[0]);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}