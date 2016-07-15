u16 geometryPassShader;

GeometryBuffer geometryBuffer;

void GeometryPass(void);
void LightPass(void);
void OutPass(void);

void GeometryPass(void)
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

	// Bind Geometry Buffer Here

	glViewport(0, 0, geometryBuffer.width, geometryBuffer.height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



}
void LightPass(void)
{

}
void OutPass(void)
{

}

void GLRender(void)
{
	OpenGLGameWindow();

	engineGlobals.isRunning = true;
	while (engineGlobals.isRunning)
	{
		GeometryPass();
		LightPass();
		OutPass();
	}
}
