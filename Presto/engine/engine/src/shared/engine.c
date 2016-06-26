#include <stdio.h>

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
            OK(V("Test!"));
            FAIL(V("Oh noes!"));
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

		engineGlobals.isRunning = true;
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
		}
}

void TestRenderer(void)
{
    const int foo = 12;
	MessageBox(NULL, V("It worked!"), V("Foo!"), MB_OK);
}

void SetRenderer(const vchar* targs)
{
	static void* currentRenderer = (void*)(&RenderStub);
	void* rendererBeginPtr = (void*)(&BeginRender);

    //usize difference = currentRenderer
	//DBUG_PTR(rendererBeginPtr);
	for(;;)
	{
		if (*((u8*)(rendererBeginPtr)) == 0xE8)
		{
            ++((u8*)(rendererBeginPtr));
            isize difference = (isize)(rendererBeginPtr) - (isize)(currentRenderer);
			MessageBox(NULL, V("Found function!"), V("Alert!"), MB_OK);
			//*((usize*)(rendererBeginPtr)) = (usize)(&TestRenderer);
			//BeginRender();
			break;
		}
		++((u8*)(rendererBeginPtr));
	}
	BeginRender();
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

	SetRenderer(V("dog"));



	return(true);
}

EngineGlobals engineGlobals = { 0 };
