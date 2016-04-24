DEFINE_EXTERNAL_INTERFACE_FUNCTION(SteamAPI_Init, int, void);

void SteamInit(void)
{
	vchar steamDLLPath[MAX_PATH];
#ifdef PRESTO_ARCHITECTURE_X64
	const vchar* dllName = V("steam_api64.dll");
#else
	const vchar* dllName = V("steam_api.dll");
#endif

	Vsprintf(steamDLLPath, MAX_PATH, V("%s\\%s\\%s"), engineGlobals.exePath, V(PRESTO_BITSTRING), dllName);
	HMODULE steamDLL = LoadLibrary(steamDLLPath);

	GET_INTERFACE_TYPE(SteamAPI_Init) steamInit = (GET_INTERFACE_TYPE(SteamAPI_Init)) GetProcAddress(steamDLL, GET_INTERFACE_NAME(SteamAPI_Init));

	if (steamDLL == NULL || steamInit == NULL)
	{
		MessageBox(NULL, V("Could not start Steam API!"), V("Fatal Error"), MB_OK);
		exit(-1);
		return;
	}

	steamInit();
}
