DISABLE_WARNINGS
#include <d3d9.h>
ENABLE_WARNINGS

DEFINE_EXTERNAL_INTERFACE_FUNCTION(Direct3DCreate9, IDirect3D9*, UINT);
static GET_INTERFACE_TYPE(Direct3DCreate9) DDirect3DCreate9;
#define Direct3DCreate9 DDirect3DCreate9

HDC deviceContext;

void InitDXFunctions(void)
{
	Direct3DCreate9 = NULL;
	HMODULE d3d9DLL = LoadLibrary(V("d3d9.dll"));
	if (d3d9DLL == NULL)
		return;

	Direct3DCreate9 = (GET_INTERFACE_TYPE(Direct3DCreate9))GetProcAddress(
		d3d9DLL, "Direct3DCreate9");

	if (Direct3DCreate9 == NULL) {
		MessageBox(NULL, V("Could not load DirectX!"), V("Fatal Error!"), MB_OK);
		exit(-1);
		return;
	}

	return;
}

static LRESULT CALLBACK QuestDX9WindowCallback(HWND windowHandle, UINT message,
	WPARAM wParam, LPARAM lParam) {
	static LRESULT result = 0;

	switch (message) {
	case WM_CREATE: {
	} break;
	case WM_SIZE: {
	} break;
	case WM_DESTROY: {
	} break;
	case WM_CLOSE: {
		PostQuitMessage(0);
	} break;
	case WM_ACTIVATEAPP: {
	} break;
	default: {
		result = DefWindowProc(windowHandle, message, wParam, lParam);
	} break;
	}

	return (result);
}

void OpenDX9GameWindow()
{
	static bool inittedDXFunctions = false;
	if (inittedDXFunctions == false)
		InitDXFunctions();
	inittedDXFunctions = true;

	WNDCLASS windowClass = { 0 };
	windowClass.style = CS_OWNDC;
	windowClass.lpfnWndProc = QuestDX9WindowCallback;
	windowClass.hInstance = GetModuleHandle(NULL);
	// windowClass.hIcon =
	windowClass.lpszClassName = V("QuestGLWindowClass");
	if (RegisterClass(&windowClass) == (int)NULL) {
		return;
	}

	HWND windowHandle = CreateWindowEx(
		0, windowClass.lpszClassName, engineGlobals.gameinfo.name,
		(WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME) | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720,
		NULL, NULL, windowClass.hInstance, NULL);

	if (windowHandle == NULL) {
		return;
	}

	d3d9Globals = (DirectX9Vars){ 0 };

	d3d9Globals.d3dInterface = Direct3DCreate9(D3D_SDK_VERSION);

	if (d3d9Globals.d3dInterface == NULL)
	{
		return;
	}

	IDirect3D9_GetDeviceCaps(d3d9Globals.d3dInterface, D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &d3d9Globals.deviceCapabilities);

	// supports shadermodel 2.0?

	int vertexProcessingType;
	if (d3d9Globals.deviceCapabilities.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vertexProcessingType = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vertexProcessingType = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	d3d9Globals.presentationParams.BackBufferWidth = 1280;
	d3d9Globals.presentationParams.BackBufferHeight = 720;
	d3d9Globals.presentationParams.Windowed = true;
	d3d9Globals.presentationParams.BackBufferCount = 1;
	d3d9Globals.presentationParams.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3d9Globals.presentationParams.MultiSampleType = D3DMULTISAMPLE_NONE; // antialiasing TODO(Questn): CONFIG ME!
	d3d9Globals.presentationParams.MultiSampleQuality = 0;
	d3d9Globals.presentationParams.hDeviceWindow = windowHandle;
	d3d9Globals.presentationParams.EnableAutoDepthStencil = true;
	d3d9Globals.presentationParams.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3d9Globals.presentationParams.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3d9Globals.presentationParams.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	d3d9Globals.presentationParams.SwapEffect = D3DSWAPEFFECT_DISCARD;

	IDirect3D9_CreateDevice(
		d3d9Globals.d3dInterface,
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		windowHandle,
		vertexProcessingType,
		&d3d9Globals.presentationParams,
		&d3d9Globals.device
	);

	if (d3d9Globals.device == NULL)
	{
		return;
	}

	deviceContext = GetDC(windowHandle);
}

i8 UpdateDX9GameWindow(void) {
	static MSG message;
	if (GetMessage(&message, NULL, NULL, NULL) > 0) {
		TranslateMessage(&message);
		DispatchMessage(&message);

		SwapBuffers(deviceContext);

		return (1);
	}
	else {
		return (0);
	}
}
