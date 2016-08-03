#ifndef PROPITIOUS_UTILITY_WINDOW_H
#define PROPITIOUS_UTILITY_WINDOW_H

#include <Quest/Common/BasicDefinitions.h>
#include <Quest/Common/Types.h>

void OpenGLGameWindow(void);
void UpdateGLGameWindow(void);

void OpenDX9GameWindow(void);
i8 UpdateDX9GameWindow(void);

LRESULT CALLBACK QuestWindowProc(HWND windowHandle, UINT message,
	WPARAM wParam, LPARAM lParam);

#endif
