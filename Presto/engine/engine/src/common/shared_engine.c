#include <stdio.h>

void ParseArguments(const vchar* args)
{
	vchar* token;
	Vconstcopy(args);
	token = Vstrtok(argsOwned, V("-"), NULL);
	while (token != NULL)
	{
		vchar* targs = Vstrstr(token, V(" "));
		usize position = targs - token;
		targs++;
		token[position] = '\0';

		if (Vstrcmp(token, V("game")) == 0)
		{
			usize size = (Vstrlen(targs) + 1) * sizeof(vchar);
			engineGlobals.gamePath = malloc(size);
			memcpy(engineGlobals.gamePath, targs, size);
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

// TODO(Preston): Separate render paths! This is the OPENGL RENDER PATH!!!
	OpenGLGameWindow();
	PlayMidiFile("E:\\Programming\\New\\Presto\\Presto\\game\\build\\template\\music\\motvia.mid");

	engineGlobals.isRunning = true;
	while (engineGlobals.isRunning)
	{
		if (UpdateGLGameWindow() == 0)
			engineGlobals.isRunning = false;

		GLRender();

		PollInputDevices();
	}

	return(true);
}

EngineGlobals engineGlobals = { 0 };
