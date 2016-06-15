#pragma comment(lib, "user32.lib")

#ifdef QUEST_CHARSET_UNICODE
int CALLBACK
	wWinMain(HINSTANCE instance,
					HINSTANCE prevInstance,
					PWSTR commandLine,
					int showCode)
#else
int CALLBACK
	WinMain(HINSTANCE instance,
					HINSTANCE prevInstance,
					LPSTR commandLine,
					int showCode)
#endif
{
	usize firstargsSize = (5 + 1) * sizeof(vchar);
	vchar* firstargsOwned = (vchar*)conjure(firstargsSize);
	memcpy(firstargsOwned, commandLine, firstargsSize);
	firstargsOwned[5] = '\0';

	vchar* exePath = (vchar*) conjure(MAX_PATH * sizeof(vchar));
	DWORD length = GetModuleFileName(NULL, exePath, MAX_PATH);

	if (Vstrcmp(firstargsOwned, V("-new ")) == 0)
	{
		PathRemoveFileSpec(exePath);
		vchar pathToEngineDLL[MAX_PATH];
		memcpy(pathToEngineDLL, exePath, MAX_PATH);
		Vstrcat(pathToEngineDLL, MAX_PATH, V("\\")V(QUEST_BITSTRING));
		AddDllDirectory(pathToEngineDLL);
		Vstrcat(pathToEngineDLL, MAX_PATH, V("\\engine.dll"));
		HMODULE dllHandle = LoadLibraryEx(pathToEngineDLL, NULL, LOAD_LIBRARY_SEARCH_APPLICATION_DIR | LOAD_LIBRARY_SEARCH_SYSTEM32 | LOAD_LIBRARY_SEARCH_USER_DIRS);
		if (dllHandle == NULL)
		{
			DEBUG(vchar* lastError = GetLastErrorAsString());
			MessageBox(NULL, V("Cannot load engine.dll\n\nTry verifying your game's cache."), V("Fatal Error!"), MB_OK);
			return(-1);
		}
		GET_INTERFACE_TYPE(StartEngine) startEngine = (GET_INTERFACE_TYPE(StartEngine)) GetProcAddress(dllHandle, GET_INTERFACE_NAME(StartEngine));
		if (startEngine == NULL)
		{
			DEBUG(vchar* lastError = GetLastErrorAsString());
			MessageBox(NULL, V("Could not find EngineStart symbol in engine.dll\n\nTry verifying your game's cache."), V("Fatal Error!"), MB_OK);
			return(-1);
		}
		startEngine(exePath, commandLine);
	}
	else
	{
		const usize cmdLineLength   = Vstrlen(commandLine);
		const usize newStringLength = 6;
		const usize exePathLength   = Vstrlen(exePath);

		vchar* argsOwned = conjure((cmdLineLength + exePathLength + newStringLength + 1) * sizeof(vchar));
		memcpy(argsOwned, exePath, exePathLength * sizeof(vchar));
		memcpy(argsOwned + exePathLength, V(" -new "), newStringLength * sizeof(vchar));
		memcpy(argsOwned + exePathLength + newStringLength, commandLine, (cmdLineLength + 1) * sizeof(vchar));

		STARTUPINFO startupInfo = { 0 };
		startupInfo.cb = sizeof(STARTUPINFO);
		PROCESS_INFORMATION processInfo = { 0 };

		if (!CreateProcess(exePath, argsOwned, NULL, NULL, NULL, NULL, NULL, NULL, &startupInfo, &processInfo))
		{
			MessageBox(NULL, V("Could not self-start for error-handling!"), V("Fatal Error!"), MB_OK);
		}
		else
		{
			WaitForSingleObject(processInfo.hProcess, INFINITE);
			CloseHandle(processInfo.hThread);
			CloseHandle(processInfo.hProcess);
			DWORD exitCode = -1;
			GetExitCodeProcess(processInfo.hProcess, &exitCode);

			vchar output[256];
			Vsprintfu(output, V("Application Closed: %d"), exitCode);

			MessageBox(NULL, output, V("Foo!"), MB_OK);
		}
	}

	return(0);
}
