void* ReadEntireFile(const vchar* filename)
{
	void* result = NULL;

	HANDLE fileHandle = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, 0);
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
	if (!ReadFile(fileHandle, result, (DWORD) fileSize.QuadPart, &bytesRead, NULL))
	{
		CloseHandle(fileHandle);
		murder(result);
		result = NULL;
		return(NULL);
	}

	CloseHandle(fileHandle);
	return(result);
}