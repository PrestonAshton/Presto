void GLRenderSystemGeometryPass(void);
void GLRenderSystemLightPass(void);
void GLRenderSystemOutPass(void);

GLRenderSystem g_glRenderSystem = { 0 };
GLTexture currentTextures[32];
GLMesh g_glCachedQuad = { 0 };

void GLRenderSystemSetTexture(GLTexture texture, u32 position)
{
	//if (texture.object != currentTextures[position].object)
	//{
	//	currentTextures[position] = texture;
	GLTextureBindTexture(texture, position);
	//}
}

void GLRenderSystemGeometryPass(void)
{
	GLGeometryBufferCreate(1280, 720);

	GL_FUNCTION(glEnable(GL_TEXTURE_2D));

	GLGeometryBufferBind(&g_glGeometryBuffer);
	{
		GL_FUNCTION(glViewport(0, 0, g_glGeometryBuffer.width, g_glGeometryBuffer.height));
		GL_FUNCTION(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		GL_FUNCTION(glUseProgram(g_glShaderObjects[GLGeometryPass]));
		Matrix4 cameraMatrix = CameraMatrix(&g_glRenderSystem.camera);
		GL_FUNCTION(glUniformMatrix4fv(GET_UNIFORM(GLGeometryPass, u_camera), 1, GL_FALSE, &(cameraMatrix.data[0].data[0])));
		GL_FUNCTION(glUniform3fv(GET_UNIFORM(GLGeometryPass, u_cameraPosition), 1, &(g_glRenderSystem.camera.transform.position.data[0])));

		for (u32 i = 0; i < g_glRenderSystem.data.length; i++)
		{
			EntityId entityId = g_glRenderSystem.data.entityId[i];
			GLRenderComponent* component = &(g_glRenderSystem.data.component[i]);

			GL_FUNCTION(glUniform1i(GET_UNIFORM(GLGeometryPass, u_material.diffuseMap), 0));
			GL_FUNCTION(glUniform1i(GET_UNIFORM(GLGeometryPass, u_material.normalMap), 1));

			f32 r, g, b, a;
			r = (f32)component->material.diffuseColour.r / 255.0f;
			g = (f32)component->material.diffuseColour.g / 255.0f;
			b = (f32)component->material.diffuseColour.b / 255.0f;
			a = (f32)component->material.diffuseColour.a / 255.0f;


			GL_FUNCTION(glUniform4f(GET_UNIFORM(GLGeometryPass, u_material.diffuseColour), r, g, b, a));
			GL_FUNCTION(glUniform4f(GET_UNIFORM(GLGeometryPass, u_material.specularColour), r, g, b, a));
			GL_FUNCTION(glUniform1f(GET_UNIFORM(GLGeometryPass, u_material.specularExponent), component->material.specularExponent));

			Transform transform = SceneGraphGetWorldTransform(SceneGraphGetNodeId(entityId));
			GL_FUNCTION(glUniform4fv(GET_UNIFORM(GLGeometryPass, u_transform.orientation), 1, &(transform.orientation.data[0])));
			GL_FUNCTION(glUniform3fv(GET_UNIFORM(GLGeometryPass, u_transform.position), 1, &(transform.position.data[0])));
			GL_FUNCTION(glUniform3fv(GET_UNIFORM(GLGeometryPass, u_transform.scale), 1, &(transform.scale.data[0])));

			GLRenderSystemSetTexture(component->material.diffuseMap, 0);
			GLRenderSystemSetTexture(component->material.normalMap, 1);

			GLMeshDraw(component->mesh);
		}
		GL_FUNCTION(glFlush());
	}
	GLGeometryBufferUnbind();
}

void GLRenderSystemLightPass(void)
{

}

void GLRenderSystemOutPass(void)
{

}

void GLRenderSystemOutput(void)
{
	GL_FUNCTION(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	GL_FUNCTION(glUseProgram(g_glShaderObjects[GLTargetPassThru]));
	GL_FUNCTION(glUniform1i(GET_UNIFORM(GLTargetPassThru, u_tex), 0));
	GLRenderSystemSetTexture(g_glGeometryBuffer.diffuse, 0);
	//GLTexture testCat = Hashmap_GLTextureGetValue(&g_glTextures, hash("textures/diffuse/cat.bmp"));
	//GLRenderSystemSetTexture(testCat, 0);

	// OPTIMISE ME AND GET QUAD PROPERLY!

	GLMeshDraw(g_glCachedQuad);

	//glFlush();
}

void GLRenderSystemInit(void)
{
	OpenGLGameWindow();

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);

	glClearColor(0, 0, 0, 1);

	glEnableVertexAttribArray(Position);
	glEnableVertexAttribArray(TexCoord);
	glEnableVertexAttribArray(Colour);
	glEnableVertexAttribArray(Normal);
	glEnableVertexAttribArray(Tangent);

	glBlendFunc(GL_ONE, GL_ONE);

	GLCreateShader("shaders/deferredGeometryPass.vs", "shaders/deferredGeometryPass.fs", GLGeometryPass);
	GLCreateShader("shaders/deferredLightPass.vs", "shaders/deferredPointLight.fs", GLPointLightPass);
	GLCreateShader("shaders/deferredLightPass.vs", "shaders/deferredDirectionalLight.fs", GLDirectionalLightPass);
	GLCreateShader("shaders/deferredLightPass.vs", "shaders/deferredAmbientLight.fs", GLAmbientLightPass);
	GLCreateShader("shaders/deferredLightPass.vs", "shaders/deferredSpotLight.fs", GLSpotLightPass);
	GLCreateShader("shaders/deferredLightPass.vs", "shaders/deferredOutput.fs", GLOutput);
	GLCreateShader("shaders/deferredLightPass.vs", "shaders/target.fs", GLTargetPassThru);

	// Register GeometryPass uniforms
	REGISTER_UNIFORM(GLGeometryPass, u_camera);
	REGISTER_UNIFORM(GLGeometryPass, u_cameraPosition);

	REGISTER_UNIFORM(GLGeometryPass, u_material.diffuseMap);
	REGISTER_UNIFORM(GLGeometryPass, u_material.normalMap);
	REGISTER_UNIFORM(GLGeometryPass, u_material.diffuseColour);
	REGISTER_UNIFORM(GLGeometryPass, u_material.specularColour);
	REGISTER_UNIFORM(GLGeometryPass, u_material.specularExponent);

	REGISTER_UNIFORM(GLGeometryPass, u_transform.orientation);
	REGISTER_UNIFORM(GLGeometryPass, u_transform.position);
	REGISTER_UNIFORM(GLGeometryPass, u_transform.scale);


	// Register Target Pass Thru Uniforms
	REGISTER_UNIFORM(GLTargetPassThru, u_tex);

	g_glRenderSystem.camera.farClippingPlane = 1000.0f;
	g_glRenderSystem.camera.nearClippingPlane = 0.01f;
	g_glRenderSystem.camera.fieldOfView = DegreeToRadian(90.0f);
	g_glRenderSystem.camera.orthographicScale = 0;
	g_glRenderSystem.camera.projectionType = Perspective;
	g_glRenderSystem.camera.transform = TransformIdentity;
	g_glRenderSystem.camera.viewportAspectRatio = 1280.0f / 720.0f;
	Vector3 position = { 0.0f, 0.0f, -2.0f };
	CameraLookAtEquals(&g_glRenderSystem.camera, &position, &g_straightUp);
}

void GLRenderSystemPostResourceInit(void)
{
	g_glCachedQuad = Hashmap_GLMeshGetValue(&g_glMeshes, hash("quad"));
}

void GLRenderSystemRender(void)
{
	GLRenderSystemGeometryPass();
	//GLRenderSystemLightPass();
	//GLRenderSystemOutPass();

	GLRenderSystemOutput();

	UpdateGLGameWindow();
}

void GLRenderSystemInterfaceCreate(EntityId id, u64 meshName, u64 materialName)
{
	GLRenderComponent component;
	component.mesh = Hashmap_GLMeshGetValue(&g_glMeshes, meshName);
	component.material = Hashmap_GLMaterialGetValue(&g_glMaterials, materialName);

	GLRenderSystemCreateByPtr(id, &component);
}