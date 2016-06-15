#include <xinput.h>

DEFINE_EXTERNAL_INTERFACE_FUNCTION(XInputGetState, DWORD, DWORD, XINPUT_STATE*);
DEFINE_EXTERNAL_INTERFACE_FUNCTION(XInputSetState, DWORD, DWORD, XINPUT_VIBRATION*);

static GET_INTERFACE_TYPE(XInputGetState) DXInputGetState;
static GET_INTERFACE_TYPE(XInputSetState) DXInputSetState;

#define XInputGetState DXInputGetState
#define XInputSetState DXInputSetState

int XInputStub()
{
	return(0);
}

void InitInput(void)
{
	XInputGetState = (GET_INTERFACE_TYPE(XInputGetState)) &XInputStub;
	XInputSetState = (GET_INTERFACE_TYPE(XInputSetState)) &XInputStub;

	HMODULE xInputHandle = LoadLibrary(V("xinput1_3.dll"));
	if (xInputHandle == NULL)
		return;

	XInputGetState = (GET_INTERFACE_TYPE(XInputGetState)) GetProcAddress(xInputHandle, "XInputGetState");
	XInputSetState = (GET_INTERFACE_TYPE(XInputSetState)) GetProcAddress(xInputHandle, "XInputSetState");
}

void PollInputDevices(void)
{
  for (u8 i = 0; i < XUSER_MAX_COUNT; i++)
  {
    XINPUT_STATE controllerState;
    if (XInputGetState(i, &controllerState) == ERROR_SUCCESS)
    {
      XINPUT_GAMEPAD* gamePad = &controllerState.Gamepad;
      b8 up = (gamePad->wButtons & XINPUT_GAMEPAD_DPAD_UP) ? 1 : 0;
      b8 down = (gamePad->wButtons & XINPUT_GAMEPAD_DPAD_DOWN) ? 1 : 0;
      b8 left = (gamePad->wButtons & XINPUT_GAMEPAD_DPAD_LEFT) ? 1 : 0;
      b8 right = (gamePad->wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) ? 1 : 0;

      b8 start = (gamePad->wButtons & XINPUT_GAMEPAD_START) ? 1 : 0;
      b8 back = (gamePad->wButtons & XINPUT_GAMEPAD_BACK) ? 1 : 0;

      b8 leftThumb = (gamePad->wButtons & XINPUT_GAMEPAD_LEFT_THUMB) ? 1 : 0;
      b8 rightThumb = (gamePad->wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) ? 1 : 0;

      b8 leftShoulder = (gamePad->wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) ? 1 : 0;
      b8 rightShoulder = (gamePad->wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) ? 1 : 0;

      b8 a = (gamePad->wButtons & XINPUT_GAMEPAD_A) ? 1 : 0;
	  if (a == 1)
		  MessageBox(NULL, V("A PRESSED :O"), V("OMG!"), MB_OK);
      b8 b = (gamePad->wButtons & XINPUT_GAMEPAD_B) ? 1 : 0;
      b8 x = (gamePad->wButtons & XINPUT_GAMEPAD_X) ? 1 : 0;
      b8 y = (gamePad->wButtons & XINPUT_GAMEPAD_Y) ? 1 : 0;

      i16 lstickX = gamePad->sThumbLX;
      i16 lstickY = gamePad->sThumbLY;
      i16 rstickX = gamePad->sThumbRX;
      i16 rstickY = gamePad->sThumbRY;
    }
    else
    {
      // TODO(Questn): Do something when controller is unavailable.
    }
  }
}
