DISABLE_WARNINGS
#include <stdio.h>
ENABLE_WARNINGS

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
			Assert(1 == 0);
		}

		if (Vstrequal(token, V("renderer")))
		{
			SetRenderer(targs);
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

void BeginRender(void)
{
	//if (engineGlobals.renderEngine == OpenGL)
	//{
		//OpenGLGameWindow();

	/*engineGlobals.isRunning = true;
	while (engineGlobals.isRunning)
	{
		//if (UpdateGLGameWindow() == 0)
		//	engineGlobals.isRunning = false;

		//GLRender();
		//MessageBox(NULL, V("Blah!"), V("Blah!"), MB_OK);
		//MessageBox(NULL, V("Rendering Frame..."), V("Foo!"), MB_OK);
		RenderStub();

		UpdateConsole();

		//PollInputDevices();
	//}
	}*/

	engineGlobals.renderSystem->RenderFunction();

	BeginRender();
}

void TestRenderer(void)
{
	MessageBox(NULL, V("It worked!"), V("Foo!"), MB_OK);
}

void EngineUpdate(void)
{
	UpdateConsole();
}

void InitialiseRenderFactory(void)
{
	static b8 initialised = false;
	if (initialised)
		return;
	initialised = true;
	engineGlobals.renderFactory = HashmapCreate();

	RenderSystem* renderStubSystem = spawn(sizeof(RenderSystem));
	renderStubSystem->RenderFunction = &RenderStub;

	engineGlobals.renderSystem = renderStubSystem;
	HashmapSet(&(engineGlobals.renderFactory), hash("stub"), &renderStubSystem);
	RenderSystem* system = (RenderSystem*)HashmapGet(&(engineGlobals.renderFactory), hash("stub"));
}

void SetRenderer(const a8* args)
{
	/*static void* currentRenderer = (void*)(RenderStub);
	void* rendererBeginPtr = (void*)(&BeginRender);

	if (*((u8*)(rendererBeginPtr)) == 0xE9)
	{
		((u8*)(rendererBeginPtr))++;
		i32 difference = (*((i32*)(rendererBeginPtr)));
		difference = ENDIAN_SWAP32(difference);
		DBUG(V("Difference from jump to BeginRender = %d"), difference);
	}

	//usize difference = currentRenderer
	//DBUG_PTR(rendererBeginPtr);
	for (;;)
	{
		if (*((u8*)(rendererBeginPtr)) == 0xE8)
		{
			++((u8*)(rendererBeginPtr));
			isize difference = (isize)(rendererBeginPtr)-(isize)(currentRenderer);
			DBUG(V("Difference from TestRenderer to RenderStub = %d"), difference);
			//*((usize*)(rendererBeginPtr)) = (usize)(&TestRenderer);
			//BeginRender();
			break;
		}
		++((u8*)(rendererBeginPtr));
	}
	BeginRender();*/

	engineGlobals.isRunning = false;
	RenderSystem* system = (RenderSystem*)HashmapGet(&(engineGlobals.renderFactory), hash("stub"));
	engineGlobals.renderSystem = system;
}


b8 StartEngine(const vchar* dir, const vchar* args)
{
	const usize dirSize = sizeof(vchar) * (Vstrlen(dir) + 1);
	engineGlobals.exePath = spawn(dirSize);
	copyMemory(dir, engineGlobals.exePath, dirSize);
#ifdef QUEST_STEAM
	SteamInit();
#endif
	ParseArguments(args);
	InitInput();

	SetRenderer("stub");

	BeginRender();

	return(true);
}

EngineGlobals engineGlobals = { 0 };
