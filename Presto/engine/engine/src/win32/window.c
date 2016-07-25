LRESULT CALLBACK QuestWindowProc(HWND windowHandle, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	static LRESULT result = 0;
	switch (message)
	{

	case WM_KEYDOWN:
	{
		keyStates[wParam] = true;
	} break;

	case WM_KEYUP:
	{
		keyStates[wParam] = false;
	} break;

	default:
		result = DefWindowProc(windowHandle, message, wParam, lParam);
	}

	return result;
}