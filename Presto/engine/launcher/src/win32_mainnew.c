forceinline vchar* GetExePath(void)
{
	vchar* path = malloc(MAX_PATH * sizeof(vchar));
	GetModuleFileName(NULL, path, MAX_PATH);
	PathRemoveFileSpec(path);
	return path;
}

forceinline vchar* GetExeFilePath(void)
{
	vchar* path = malloc(MAX_PATH * sizeof(vchar));
	GetModuleFileName(NULL, path, MAX_PATH);
	return path;
}

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
	vchar* token;
	Vconstcopy(commandLine);
	token = Vstrtok(commandLineOwned, V("-"));
	while (token != NULL)
	{
		vchar* targs = Vstrstr(token, V(" "));
		if (targs != NULL)
		{
			usize position = targs - token;
			targs++;
			token[position] = '\0';
		}

		if (Vstrequal(token, V("new")))
		{
			vchar* exePath = GetExePath();

			vchar* pathToEngineDLL = conjure(MAX_PATH * sizeof(vchar));
			Vsprintf(pathToEngineDLL, MAX_PATH, V("%s/%s/engine.dll"), exePath, V(QUEST_BITSTRING));

			HMODULE dllHandle = LoadLibraryEx(pathToEngineDLL, NULL, LOAD_LIBRARY_SEARCH_APPLICATION_DIR | LOAD_LIBRARY_SEARCH_SYSTEM32 | LOAD_LIBRARY_SEARCH_USER_DIRS);
			if (dllHandle == NULL)
			{
				MessageBox(NULL, V("Cannot load engine.dll\n\nTry verifying your game's cache."), V("Fatal Error!"), MB_OK);
				return;
			}

			GET_INTERFACE_TYPE(StartEngine) startEngine = (GET_INTERFACE_TYPE(StartEngine)) GetProcAddress(dllHandle, GET_INTERFACE_NAME(StartEngine));
			if (startEngine == NULL)
			{
				MessageBox(NULL, V("Could not find EngineStart symbol in engine.dll\n\nTry verifying your game's cache."), V("Fatal Error!"), MB_OK);
				return;
			}

			startEngine(exePath, commandLine);
		}

		token = Vstrtok(NULL, V("-"));
	}

	vchar* exePath = GetExeFilePath();
	// 5 from strlen("-new ") // 3 from spaces
	usize size = Vstrlen(exePath) + (Vstrlen(commandLine) + 8);
	vchar* newCmdLine = conjure(size * sizeof(vchar));

	Vsprintf(newCmdLine, size, V("%s %s %s"), exePath, V("-new"), commandLine);

	STARTUPINFO sInfo = { 0 };
	sInfo.cb = sizeof(STARTUPINFO);
	PROCESS_INFORMATION pInfo = { 0 };
	if (!CreateProcess(exePath, newCmdLine, NULL, NULL, NULL, NULL, NULL, NULL, &sInfo, &pInfo))
		MessageBox(NULL, V("Could not self-start for error-handling!"), V("Fatal Error!"), MB_OK);
	else
	{
		WaitForSingleObject(pInfo.hProcess, INFINITE);
		CloseHandle(pInfo.hThread);
		CloseHandle(pInfo.hProcess);
		DWORD exitCode = -1;
		GetExitCodeProcess(pInfo.hProcess, &exitCode);
	}
}