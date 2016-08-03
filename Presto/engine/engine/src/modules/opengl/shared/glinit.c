void InitGLRenderSystem(void);

INITIALIZER(InitGLRenderSystem);

void InitGLRenderSystem(void)
{
	InitialiseRenderFactory();

	Renderer glRenderer = { 0 };
	usize* glRendererPtr = &glRenderer;

	for (u32 i = 0; i < (sizeof(Renderer) / sizeof(usize)); i++)
	{
		glRendererPtr[i] = &BlankFunction;
	}

	glRenderer.mesh.AddFromData = &GLMeshAddMesh;
	glRenderer.texture.CreateFromFile = &GLTextureAddFromFile;
	glRenderer.texture.CreateFromData = &GLTextureAddFromData;
	glRenderer.material.CreateFromData = &GLMaterialAddFromData;
	glRenderer.renderSystem.Create = &GLRenderSystemInterfaceCreate;
	glRenderer.Init = &GLRenderSystemInit;
	glRenderer.Render = &GLRenderSystemRender;
	glRenderer.PostResourceInit = &GLRenderSystemPostResourceInit;

	Hashmap_RendererSetByPtr(&g_renderers, hash("opengl"), &glRenderer);
}

