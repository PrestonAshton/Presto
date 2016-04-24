DEFINE_EXTERNAL_INTERFACE_FUNCTION(wglCreateContext, HGLRC, HDC);
DEFINE_EXTERNAL_INTERFACE_FUNCTION(wglDeleteContext, BOOL, HGLRC);
DEFINE_EXTERNAL_INTERFACE_FUNCTION(wglMakeCurrent, BOOL, HDC, HGLRC);
DEFINE_EXTERNAL_INTERFACE_FUNCTION(wglGetProcAddress, PROC, LPCSTR);
static GET_INTERFACE_TYPE(wglCreateContext) DwglCreateContext;
static GET_INTERFACE_TYPE(wglDeleteContext) DwglDeleteContext;
static GET_INTERFACE_TYPE(wglMakeCurrent) DwglMakeCurrent;
static GET_INTERFACE_TYPE(wglGetProcAddress) DwglGetProcAddress;
#define wglCreateContext DwglCreateContext
#define wglDeleteContext DwglDeleteContext
#define wglMakeCurrent DwglMakeCurrent
#define wglGetProcAddress DwglGetProcAddress

static void InitWGLFunctions() {
  wglCreateContext = NULL;
  wglDeleteContext = NULL;
  wglMakeCurrent = NULL;
  wglGetProcAddress = NULL;
  HMODULE openGLHandle = LoadLibrary(V("opengl32.dll"));
  if (openGLHandle == NULL)
    return;

  wglCreateContext = (GET_INTERFACE_TYPE(wglCreateContext))GetProcAddress(
      openGLHandle, "wglCreateContext");
  wglDeleteContext = (GET_INTERFACE_TYPE(wglDeleteContext))GetProcAddress(
      openGLHandle, "wglDeleteContext");
  wglMakeCurrent = (GET_INTERFACE_TYPE(wglMakeCurrent))GetProcAddress(
      openGLHandle, "wglMakeCurrent");
  wglGetProcAddress = (GET_INTERFACE_TYPE(wglGetProcAddress))GetProcAddress(
      openGLHandle, "wglGetProcAddress");

  if (wglCreateContext == NULL || wglDeleteContext == NULL ||
      wglMakeCurrent == NULL || wglGetProcAddress == NULL) {
    MessageBox(NULL, V("Could not load OpenGL!"), V("Fatal Error!"), MB_OK);
    exit(-1);
    return;
  }

  return;
}

static HGLRC glRenderingContext;
static HDC deviceContext;

static LRESULT CALLBACK PrestoGLWindowCallback(HWND windowHandle, UINT message,
                                               WPARAM wParam, LPARAM lParam) {
  static LRESULT result = 0;

  switch (message) {
  case WM_CREATE: {
    PIXELFORMATDESCRIPTOR pixelFormatDescription = {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, // Flags
        PFD_TYPE_RGBA, // The kind of framebuffer. RGBA or palette.
        32,            // Colordepth of the framebuffer.
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        24, // Number of bits for the depthbuffer
        8,  // Number of bits for the stencilbuffer
        0,  // Number of Aux buffers in the framebuffer.
        PFD_MAIN_PLANE,
        0,
        0,
        0,
        0};

    deviceContext = GetDC(windowHandle);
    int pixelFormat = NULL;
    pixelFormat = ChoosePixelFormat(deviceContext, &pixelFormatDescription);
    SetPixelFormat(deviceContext, pixelFormat, &pixelFormatDescription);
    glRenderingContext = wglCreateContext(deviceContext);
    wglMakeCurrent(deviceContext, glRenderingContext);

	static b8 glInitState = false;
	ogl_LoadFunctions();
	glInitState = true;
  } break;
  case WM_SIZE: {
  } break;
  case WM_DESTROY: {
  } break;
  case WM_CLOSE: {
    wglMakeCurrent(deviceContext, NULL);
    wglDeleteContext(glRenderingContext);
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

void OpenGLGameWindow() {
  glRenderingContext = NULL;
  deviceContext = NULL;

  static b8 wglInitState = false;
  InitWGLFunctions();
  wglInitState = true;

  WNDCLASS windowClass = {0};
  windowClass.style = CS_OWNDC;
  windowClass.lpfnWndProc = PrestoGLWindowCallback;
  windowClass.hInstance = GetModuleHandle(NULL);
  // windowClass.hIcon =
  windowClass.lpszClassName = V("PrestoGLWindowClass");

  if (RegisterClass(&windowClass) == NULL) {
    return;
  }

  HWND windowHandle = CreateWindowEx(
      0, windowClass.lpszClassName, engineGlobals.gameinfo.name,
      WS_OVERLAPPEDWINDOW  ^ WS_THICKFRAME | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720,
      NULL, NULL, windowClass.hInstance, NULL);

  if (windowHandle == NULL) {
    return;
  }
}

i8 UpdateGLGameWindow(void) {
  static MSG message;
  if (GetMessage(&message, NULL, NULL, NULL) > 0) {
    TranslateMessage(&message);
    DispatchMessage(&message);

    SwapBuffers(deviceContext);

    return (1);
  } else {
    return (0);
  }
}
