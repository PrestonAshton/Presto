DirectX9Vars d3d9Globals;

void DX9Render(void)
{
	IDirect3DDevice9Ex_Clear(d3d9Globals.device, 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	IDirect3DDevice9Ex_BeginScene(d3d9Globals.device);
	IDirect3DDevice9Ex_EndScene(d3d9Globals.device);
	IDirect3DDevice9Ex_Present(d3d9Globals.device, NULL, NULL, NULL, NULL);
}
