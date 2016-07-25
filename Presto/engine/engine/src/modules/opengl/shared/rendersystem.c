void GeometryPass(void);
void LightPass(void);
void OutPass(void);

GLRenderSystem g_glRenderSystem = { 0 };
GLTexture currentTextures[32];

void GLRenderSystemSetTexture(GLTexture texture, u32 position)
{
	if (texture.object != currentTextures[position].object)
	{
		currentTextures[position] = texture;
		GLTextureBindTexture(texture, position);
	}
}

void GLRenderSystemGeometryPass(void)
{
	GLGeometryBufferCreate(1280, 720);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

	GLGeometryBufferBind(&g_glGeometryBuffer);
	{
		glViewport(0, 0, g_glGeometryBuffer.width, g_glGeometryBuffer.height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(g_glShaderObjects[GLGeometryPass]);
		Matrix4 cameraMatrix = CameraMatrix(&g_glRenderSystem.camera);
		glUniformMatrix4fv(GET_UNIFORM(GLGeometryPass, u_camera), 1, GL_FALSE, &(cameraMatrix.data[0].data[0]));
		glUniform3fv(GET_UNIFORM(GLGeometryPass, u_cameraPosition), 1, &(g_glRenderSystem.camera.transform.position.data[0]));

		for (u32 i = 0; i < g_glRenderSystem.data.length; i++)
		{
			EntityId entityId = g_glRenderSystem.data.entityId[i];
			GLRenderComponent* component = &(g_glRenderSystem.data.component[i]);

			glUniform1ui(GET_UNIFORM(GLGeometryPass, u_material_diffuseMap), 0);
			glUniform1ui(GET_UNIFORM(GLGeometryPass, u_material_normalMap), 1);

			f32 r, g, b, a;
			r = (f32)component->material.diffuseColour.r / 255.0f;
			g = (f32)component->material.diffuseColour.g / 255.0f;
			b = (f32)component->material.diffuseColour.b / 255.0f;
			a = (f32)component->material.diffuseColour.a / 255.0f;

			glUniform4f(GET_UNIFORM(GLGeometryPass, u_material_diffuseColour), r, g, b, a);
			glUniform4f(GET_UNIFORM(GLGeometryPass, u_material_specularColour), r, g, b, a);
			glUniform1f(GET_UNIFORM(GLGeometryPass, u_material_specularExponent), component->material.specularExponent);

			Transform transform = SceneGraphGetWorldTransform(SceneGraphGetNodeId(entityId));
			glUniform4fv(GET_UNIFORM(GLGeometryPass, u_transform_orientation), 1, &(transform.orientation.data[0]));
			glUniform3fv(GET_UNIFORM(GLGeometryPass, u_transform_position), 1, &(transform.position.data[0]));
			glUniform3fv(GET_UNIFORM(GLGeometryPass, u_transform_scale), 1, &(transform.scale.data[0]));

			GLRenderSystemSetTexture(component->material.diffuseMap, 0);
			GLRenderSystemSetTexture(component->material.normalMap, 1);

			GLMeshDraw(component->mesh);
		}
		glFlush();
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
	glClearColor(1, 1, 1, 1);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(g_glShaderObjects[GLTargetPassThru]);
	glUniform1i(GET_UNIFORM(GLTargetPassThru, u_tex), 0);
	GLRenderSystemSetTexture(g_glGeometryBuffer.diffuse, 0);

	// OPTIMISE ME AND GET QUAD PROPERLY!

	GLMeshDraw(Hashmap_GLMeshGetValue(&g_glMeshes, hash("quad")));

	glFlush();
}

void GLRenderSystemInit(void)
{
	OpenGLGameWindow();

	/*glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);*/

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

	// Register Geometry Pass Uniforms
	GLRegisterUniform(u_camera, GLGeometryPass, "u_camera");
	GLRegisterUniform(u_cameraPosition, GLGeometryPass, "u_cameraPosition");
	GLRegisterUniform(u_material_diffuseMap, GLGeometryPass, "u_material.diffuseMap");
	GLRegisterUniform(u_material_normalMap, GLGeometryPass, "u_material.normalMap");
	GLRegisterUniform(u_material_diffuseColour, GLGeometryPass, "u_material.diffuseColour");
	GLRegisterUniform(u_material_specularColour, GLGeometryPass, "u_material.specularColour");
	GLRegisterUniform(u_material_specularExponent, GLGeometryPass, "u_material.specularExponent");
	GLRegisterUniform(u_transform_orientation, GLGeometryPass, "u_transform.orientation");
	GLRegisterUniform(u_transform_position, GLGeometryPass, "u_transform.position");
	GLRegisterUniform(u_transform_scale, GLGeometryPass, "u_transform.scale");

	// Register Target Pass Thru Uniforms
	GLRegisterUniform(u_tex, GLTargetPassThru, "u_tex");

	g_glRenderSystem.camera.farClippingPlane = 1000.0f;
	g_glRenderSystem.camera.nearClippingPlane = 0.01f;
	g_glRenderSystem.camera.fieldOfView = DegreeToRadian(90.0f);
	g_glRenderSystem.camera.orthographicScale = 0;
	g_glRenderSystem.camera.projectionType = Perspective;
	g_glRenderSystem.camera.transform = TransformIdentity;
	g_glRenderSystem.camera.viewportAspectRatio = 1280.0f / 720.0f;
	Vector3 position = { 0.0f, 0.0f, -2.0f };
	//CameraLookAtEquals(&g_glRenderSystem.camera, &position, &g_straightUp);
}

// clear colour test

void GLRenderSystemRender(void)
{
	GLRenderSystemGeometryPass();
	GLRenderSystemLightPass();
	GLRenderSystemOutPass();

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