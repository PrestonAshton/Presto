#include <stdio.h>

void ParseArguments(const vchar* args)
{
	vchar* token;
	Vconstcopy(args);
	token = Vstrtok(argsOwned, V("-"), NULL);
	while (token != NULL)
	{
		vchar* targs = Vstrstr(token, V(" "));
		if (targs != NULL)
		{
			usize position = targs - token;
			targs++;
			token[position] = '\0';
		}

		if (!Vstrcmp(token, V("game")))
		{
			usize size = (Vstrlen(targs) + 1) * sizeof(vchar);
			engineGlobals.gamePath = malloc(size);
			memcpy(engineGlobals.gamePath, targs, size);
		}

		if (!Vstrcmp(token, V("console")))
		{
			OpenConsole();
			WriteLineToConsole(V("Console Opened!"), (Colour24) { 255, 0, 0 });
			WriteLineToConsole(V("Console Opened 2!"), (Colour24) { 0, 0, 0 });
		}

		if (!Vstrcmp(token, V("renderer")))
		{
			if (!Vstrcmp(targs, V("opengl")) ||
				!Vstrcmp(targs, V("gl")) ||
				!Vstrcmp(targs, V("ogl")))
				engineGlobals.renderEngine = OpenGL;

			if (!Vstrcmp(targs, V("d3d9")) ||
				!Vstrcmp(targs, V("directx9")))
				engineGlobals.renderEngine = DirectX9;

			if (!Vstrcmp(targs, V("d3d10")) ||
				!Vstrcmp(targs, V("directx10")))
				engineGlobals.renderEngine = DirectX10;

			if (!Vstrcmp(targs, V("d3d11")) ||
				!Vstrcmp(targs, V("directx11")))
				engineGlobals.renderEngine = DirectX11;

			if (!Vstrcmp(targs, V("d3d12")) ||
				!Vstrcmp(targs, V("directx12")))
				engineGlobals.renderEngine = DirectX12;

			if (!Vstrcmp(targs, V("vulkan")))
				engineGlobals.renderEngine = Vulkan;
		}

		token = Vstrtok(NULL, V("-"), NULL);
	}
}

void ReadGameInfo(void)
{

}

b8 StartEngine(const vchar* dir, const vchar* args)
{
	const usize dirSize = sizeof(vchar) * (Vstrlen(dir) + 1);
	engineGlobals.exePath = malloc(dirSize);
	memcpy(engineGlobals.exePath, dir, dirSize);
#ifdef PRESTO_STEAM
	SteamInit();
#endif
	ParseArguments(args);
	InitInput();

	//PlayMidiFile("");
	Array foo = ArrayCreate(int);
	int item = 123;
	ArrayPushBack(&foo, &item);
	int dog = *((int*)(ArrayGet(&foo, 0)));

	if (engineGlobals.renderEngine == OpenGL)
	{
		OpenGLGameWindow();

		engineGlobals.isRunning = true;
		while (engineGlobals.isRunning)
		{
			if (UpdateGLGameWindow() == 0)
				engineGlobals.isRunning = false;

			GLRender();

			PollInputDevices();
		}
	}
	else if (engineGlobals.renderEngine == DirectX9)
	{
		OpenDX9GameWindow();

		engineGlobals.isRunning = true;
		while (engineGlobals.isRunning)
		{
			if (UpdateDX9GameWindow() == 0)
				engineGlobals.isRunning = false;

			DX9Render();

			PollInputDevices();
		}
	}

	return(true);
}

EngineGlobals engineGlobals = { 0 };
