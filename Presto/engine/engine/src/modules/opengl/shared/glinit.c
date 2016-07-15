void InitGLRenderSystem(void);

INITIALIZER(InitGLRenderSystem);

void InitGLRenderSystem(void)
{
	InitialiseRenderFactory();

	RenderSystem glRenderSystem;
	glRenderSystem.RenderFunction = &GLRender;

	HashmapSet(&(engineGlobals.renderFactory), hash("opengl"), &glRenderSystem);
}

