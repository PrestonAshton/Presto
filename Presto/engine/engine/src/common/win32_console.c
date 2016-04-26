#include <stdio.h>
#include <io.h>
#include <fcntl.h>

static int maxBuffers = 0;
static vchar* textBuffers[1024];
static Colour24 colourBuffers[1024];

static LRESULT CALLBACK PrestoConsoleWindowCallback(HWND windowHandle, UINT message,
	WPARAM wParam, LPARAM lParam) {
	static LRESULT result = 0;

	switch (message) {
	case WM_CREATE: {
	} break;
	case WM_SIZE: {
	} break;
	case WM_PAINT: {
		PAINTSTRUCT paint;
		HDC deviceContext = BeginPaint(windowHandle, &paint);

		int height = -MulDiv(10, GetDeviceCaps(deviceContext, LOGPIXELSY), 72);

		HFONT font = CreateFont(
			height, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE,
			DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			CLEARTYPE_QUALITY, FF_DONTCARE, V("Consolas"));

		SelectObject(deviceContext, font);

		for (usize i = 0; i < maxBuffers; i++)
		{
			RECT paintPos = paint.rcPaint;
			paintPos.top = (LONG)((-height) * i);
			COLORREF colour = RGB(colourBuffers[i].r, colourBuffers[i].g, colourBuffers[i].b);
			SetTextColor(deviceContext, colour);
			DrawText(deviceContext, textBuffers[i], -1, &paintPos, DT_LEFT | DT_EDITCONTROL);
		}
		EndPaint(windowHandle, &paint);
	} break;
	case WM_DESTROY: {
	} break;
	case WM_CLOSE: {
		DestroyWindow(windowHandle);
	} break;
	case WM_ACTIVATEAPP: {
	} break;
	default: {
		result = DefWindowProc(windowHandle, message, wParam, lParam);
	} break;
	}

	return (result);
}

void OpenConsole(void)
{
	WNDCLASS windowClass = { 0 };
	windowClass.style = CS_OWNDC;
	windowClass.lpfnWndProc = PrestoConsoleWindowCallback;
	windowClass.hInstance = GetModuleHandle(NULL);
	// windowClass.hIcon =
	windowClass.lpszClassName = V("PrestoConsoleWindowClass");

	if (RegisterClass(&windowClass) == NULL) {
		return;
	}

	HWND windowHandle = CreateWindowEx(
		0, windowClass.lpszClassName, V("Presto Developer Console"),
		WS_OVERLAPPEDWINDOW  ^ WS_THICKFRAME | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 800, 450,
		NULL, NULL, windowClass.hInstance, NULL);

	if (windowHandle == NULL) {
		return;
	}
}

void WriteToConsole(const vchar* text, Colour24 colour)
{
	usize textSize = Vstrlen(text + 1) * sizeof(vchar);
	textBuffers[maxBuffers] = malloc(textSize);
	memcpy(textBuffers[maxBuffers], text, textSize + 4);
	colourBuffers[maxBuffers] = colour;
	maxBuffers++;
}

void WriteLineToConsole(const vchar* text, Colour24 colour)
{
	usize textLength = Vstrlen(text);
	usize textSize = (textLength + 2) * sizeof(vchar);
	vchar* textBuffer = malloc(textSize);
	memcpy(textBuffer, text, textSize);
	textBuffer[textLength] = V('\n');
	textBuffer[textLength + 1] = V('\0');

	WriteToConsole(textBuffer, colour);
}