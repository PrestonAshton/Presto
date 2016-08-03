vchar* GetEngineLockPath(void)
{
	vchar buffer[2048] = { 0 };
	GetModuleFileName(NULL, buffer, 2048);
	PathRemoveFileSpec(buffer);
	Vstrcat(buffer, 2048, V("\\game.lck"));
	return buffer;
}

void OpenEngineLock(void)
{
	vchar* path = GetEngineLockPath();
	CreateFile(path, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
}

void CloseEngineLock(void)
{
	vchar* path = GetEngineLockPath();
	DeleteFile(path);
}

void* ReadEntireFile(const a8* filename)
{
	vchar* wideName = conjure((strlen(filename) + 1) * sizeof(vchar));
	Vforcevcharfromchar(wideName, filename);
	wideName[strlen(filename)] = V('\0');
	void* result = NULL;

	const wchar_t* finalPath = conjure(MAX_PATH * sizeof(vchar));
	Vsprintf(finalPath, MAX_PATH, V("%s/%s/%s"), engineGlobals.exePath, engineGlobals.gamePath, wideName);

	HANDLE fileHandle = CreateFile(finalPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, 0);
	if (fileHandle == INVALID_HANDLE_VALUE)
	{
		return(NULL);
	}

	LARGE_INTEGER fileSize;
	if (!GetFileSizeEx(fileHandle, &fileSize))
	{
		CloseHandle(fileHandle);
		return(NULL);
	}

	result = spawn(fileSize.QuadPart);
	Assert(fileSize.QuadPart <= (u32)(-1));
	DWORD bytesRead;
	// TODO(Questn): FIX ME FOR BIGGER FILES!
	if (!ReadFile(fileHandle, result, (DWORD)fileSize.QuadPart, &bytesRead, NULL))
	{
		CloseHandle(fileHandle);
		murder(result);
		result = NULL;
		return(NULL);
	}

	CloseHandle(fileHandle);
	return result;
}

a8* ReadEntireTextFile(const a8* filename)
{
	vchar* wideName = conjure((strlen(filename) + 1) * sizeof(vchar));
	Vforcevcharfromchar(wideName, filename);
	wideName[strlen(filename)] = V('\0');
	a8* result = NULL;

	const wchar_t* finalPath = conjure(MAX_PATH * sizeof(vchar));
	Vsprintf(finalPath, MAX_PATH, V("%s/%s/%s"), engineGlobals.exePath, engineGlobals.gamePath, wideName);

	HANDLE fileHandle = CreateFile(finalPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, 0);
	if (fileHandle == INVALID_HANDLE_VALUE)
	{
		return(NULL);
	}

	LARGE_INTEGER fileSize;
	if (!GetFileSizeEx(fileHandle, &fileSize))
	{
		CloseHandle(fileHandle);
		return(NULL);
	}

	result = spawn(fileSize.QuadPart);
	Assert(fileSize.QuadPart <= (u32)(-1));
	DWORD bytesRead;
	// TODO(Questn): FIX ME FOR BIGGER FILES!
	if (!ReadFile(fileHandle, result, (DWORD)fileSize.QuadPart, &bytesRead, NULL))
	{
		CloseHandle(fileHandle);
		murder(result);
		result = NULL;
		return(NULL);
	}

	CloseHandle(fileHandle);
	result[fileSize.QuadPart] = '\0';
	return result;
}