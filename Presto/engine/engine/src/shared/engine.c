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
			WriteLineToConsole(V("Console Opened!"), (Colour24) { 255, 0, 0 });
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
			MessageBox(NULL, V("Render Stub Called"), V("Foo!"), MB_OK);
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
			MessageBox(NULL, V("Rendering Frame..."), V("Foo!"), MB_OK);
			RenderStub();

			//PollInputDevices();
		//}
		}
}

void TestRenderer(void)
{
	MessageBox(NULL, V("It worked!"), V("Foo!"), MB_OK);
}

void SetRenderer(const vchar* targs)
{
	static usize* currentRenderer = (usize*)(&RenderStub);
	usize* rendererBeginPtr = (usize*)(&BeginRender);

	for(;;)
	{
		if (*rendererBeginPtr == (usize) currentRenderer)
		{
			MessageBox(NULL, V("Found function!"), V("Alert!"), MB_OK);
			*rendererBeginPtr = (usize)(&TestRenderer);
			BeginRender();
			break;
		}
		rendererBeginPtr++;
	}
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

	//PlayMidiFile("");
	Array foo = ArrayCreate(int);
	int item = 123;
	ArrayPushBack(&foo, &item);
	int dog = *((int*)(ArrayGet(&foo, 0)));

	SetRenderer(V("dog"));

	return(true);
}

EngineGlobals engineGlobals = { 0 };
