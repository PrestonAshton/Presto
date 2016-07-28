DISABLE_WARNINGS
#include <stdio.h>
ENABLE_WARNINGS

#include <Quest/Modules/OpenAL.h>


void ParseArguments(const vchar* args)
{
	vchar* token;
	Vconstcopy(args);
	token = Vstrtok(argsOwned, V("-"));
	while (token != NULL)
	{
		vchar* targs = Vstrstr(token, V(" "));
		if (targs != NULL)
		{
			usize position = targs - token;
			targs++;
			token[position] = '\0';
		}

		if (Vstrequal(token, V("game")))
		{
			usize size = (Vstrlen(targs) + 1) * sizeof(vchar);
			engineGlobals.gamePath = spawn(size);
			copyMemory(targs, engineGlobals.gamePath, size);
		}

		if (Vstrequal(token, V("console")))
		{
			OpenConsole();
			MSG(V("Console Opened!"));
		}

		if (Vstrequal(token, V("renderer")))
		{
			a8* unwidened = conjure(Vstrlen(targs) + 1);
			Vforcechar(unwidened, targs);
			SetRenderer(unwidened);
		}

		token = Vstrtok(NULL, V("-"));
	}
}

void ReadGameInfo(void)
{

}

dontinline void RenderStub()
{
	WARN(V("Invalid Renderer!"));
}

void LoadSprite(void)
{
	MeshData data = { 0 };

	Array_VertexPushBack(&(data.vertices), CreateVertex((Vector3) { -0.5f, -0.5f, 0.0f }, (Vector2) { 0.0f, 0.0f }));
	Array_VertexPushBack(&(data.vertices), CreateVertex((Vector3) { +0.5f, -0.5f, 0.0f }, (Vector2) { 1.0f, 0.0f }));
	Array_VertexPushBack(&(data.vertices), CreateVertex((Vector3) { +0.5f, +0.5f, 0.0f }, (Vector2) { 1.0f, 1.0f }));
	Array_VertexPushBack(&(data.vertices), CreateVertex((Vector3) { -0.5f, +0.5f, 0.0f }, (Vector2) { 0.0f, 1.0f }));

	MeshDataAddFace(&data, 0, 1, 2);
	MeshDataAddFace(&data, 2, 3, 0);
	MeshDataGenerateNormals(&data);

	g_renderer.mesh.AddFromData(hash("sprite"), &data);
}

void LoadQuad(void)
{
	MeshData data = { 0 };

	Array_VertexPushBack(&(data.vertices), CreateVertex((Vector3) { -1.0f, -1.0f, 0.0f }, (Vector2) { 0.0f, 0.0f }));
	Array_VertexPushBack(&(data.vertices), CreateVertex((Vector3) { +1.0f, -1.0f, 0.0f }, (Vector2) { 1.0f, 0.0f }));
	Array_VertexPushBack(&(data.vertices), CreateVertex((Vector3) { +1.0f, +1.0f, 0.0f }, (Vector2) { 1.0f, 1.0f }));
	Array_VertexPushBack(&(data.vertices), CreateVertex((Vector3) { -1.0f, +1.0f, 0.0f }, (Vector2) { 0.0f, 1.0f }));

	MeshDataAddFace(&data, 0, 1, 2);
	MeshDataAddFace(&data, 2, 3, 0);
	MeshDataGenerateNormals(&data);

	g_renderer.mesh.AddFromData(hash("quad"), &data);
}

void LoadDefaultData(void)
{
	LoadQuad();
	LoadSprite();
}

void LoadScene(void)
{
	EntityId cat = EntityWorldCreateEntity();
	g_entityWorld.components[cat] = ComponentName;

	g_entityWorld.names[cat] = (NameComponent) { "cat" };

	g_renderer.texture.CreateFromFile("textures/diffuse/cat.bmp");
	g_renderer.texture.CreateFromFile("textures/normal/default.bmp");

	g_renderer.material.CreateFromData(hash("cat"), hash("textures/diffuse/cat.bmp"), hash("textures/normal/default.bmp"), (Colour32) {255, 255, 255, 255}, 80.0f);

	Transform transform = TransformIdentity;
	transform.position = (Vector3) { 0, 0, 0 };
	NodeId catNode = SceneGraphCreate(cat, &transform);

	g_renderer.renderSystem.Create(cat, hash("sprite"), hash("cat"));
}

void BeginRender(void)
{
	g_renderer.Init();
	g_soundHandler.Init();

	g_soundHandler.Cache("sound/ui/select.wav");
	g_soundHandler.Cache("sound/ui/startup.wav");
	g_soundHandler.Play(hash("sound/ui/startup.wav"));

	LoadDefaultData();
	LoadScene();

	TickCounter tc = TickCounterCreate();
	Time prevTime = TimeNow();

	engineGlobals.isRunning = true;
	while (engineGlobals.isRunning)
	{
		Time currentTime = TimeNow();
		Time deltaTime = TimeFromMicroseconds(currentTime.microseconds - prevTime.microseconds);
		prevTime = currentTime;

		if (KeyPressed(Left, Single) || KeyPressed(Right, Single))
			g_soundHandler.Play(hash("sound/ui/select.wav"));

		if (KeyPressed(EscapeKey, Single))
			engineGlobals.isRunning = false;

		if (TickCounterUpdate(&tc, TimeFromMilliseconds(500)))
		{
			printf("Your FPS is: %f\n", tc.tickRate);
		}

		g_renderer.Render();
		UpdateConsole();
	}
}

void EngineUpdate(void)
{
	UpdateConsole();
}

Renderer renderStub = { 0 };
Renderer nullRenderer = { 0 };

void InitialiseRenderFactory(void)
{
	static b8 initialised = false;
	if (initialised)
		return;
	initialised = true;

	// Initialise all in NullRenderer to BlankFunction without doing stuff manually.
	// Lazy method!

	usize* nullRendererPtr = &nullRenderer;
	for (u32 i = 0; i < (sizeof(Renderer) / sizeof(usize)); i++)
	{
		nullRendererPtr[i] = &BlankFunction;
	}

	renderStub = nullRenderer;
	renderStub.Render = &RenderStub;

	Hashmap_RendererSetByPtr(&(g_renderers), hash("stub"), &renderStub);
	Hashmap_RendererSetByPtr(&(g_renderers), hash("null"), &nullRenderer);
	g_renderer = renderStub;
}

SoundHandler nullAudioHandler = { 0 };

void InitialiseSoundHandlerFactory(void)
{
	static b8 initialised = false;
	if (initialised)
		return;
	initialised = true;

	usize* nullAudioHandlerPtr = &nullAudioHandler;
	for (u32 i = 0; i < (sizeof(SoundHandler) / sizeof(usize)); i++)
	{
		nullAudioHandlerPtr[i] = &BlankFunction;
	}

	Hashmap_SoundHandlerSetByPtr(&(g_soundHandlers), hash("null"), &nullAudioHandler);
	g_soundHandler = nullAudioHandler;
}

void SetRenderer(const a8* args)
{
	g_renderer = Hashmap_RendererGetValueDefault(&g_renderers, hash(args), renderStub);
	// sort out stuff here!
}

void SetSoundHandler(const a8* args)
{
	g_soundHandler = Hashmap_SoundHandlerGetValueDefault(&g_soundHandlers, hash(args), nullAudioHandler);
	// sort out stuff here!
}

void StartEngine(const vchar* dir, const vchar* args)
{
	OpenEngineLock();

	const usize dirSize = sizeof(vchar) * (Vstrlen(dir) + 1);
	engineGlobals.exePath = spawn(dirSize);
	copyMemory(dir, engineGlobals.exePath, dirSize);
#ifdef QUEST_STEAM
	SteamInit();
#endif
	SetSoundHandler("openal");
	SetRenderer("opengl");

	ParseArguments(args);
	InitInput();

	BeginRender();

	CloseEngineLock();	
	return 1;
}

EngineGlobals engineGlobals = { 0 };
