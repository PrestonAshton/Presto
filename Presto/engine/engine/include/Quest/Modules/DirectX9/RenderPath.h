#ifndef QUEST_GRAPHICS_DX9RENDERPATH_H
#define QUEST_GRAPHICS_DX9RENDERPATH_H

DISABLE_WARNINGS
#include <d3d9.h>
ENABLE_WARNINGS

typedef struct
{
	LPDIRECT3D9 d3dInterface;
	LPDIRECT3DDEVICE9 device;
	D3DPRESENT_PARAMETERS presentationParams;
	D3DCAPS9 deviceCapabilities;
} DirectX9Vars;

extern DirectX9Vars d3d9Globals;

void DX9Render(void);

#endif
