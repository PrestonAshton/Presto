#ifndef PRESTO_GRAPHICS_DX9RENDERPATH_H
#define PRESTO_GRAPHICS_DX9RENDERPATH_H

#include <d3d9.h>

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
