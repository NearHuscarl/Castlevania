#pragma once

#include <d3dx9.h>
#include <Windows.h>

class GraphicsDevice
{
public:
	D3DCOLOR GetTransparentColor() { return transparentColor; }
	void SetTransparentColor(D3DCOLOR color) { transparentColor = color; }

	void CreateDevice(HWND hWnd);

	IDirect3DDevice9 *GetDevice();
	IDirect3DSurface9 *GetBackBuffer();
	ID3DXSprite *GetSpriteHandler();

	virtual ~GraphicsDevice();

private:
	D3DCOLOR transparentColor = D3DCOLOR_XRGB(255, 255, 255);

	IDirect3DDevice9 *d3ddv = nullptr;       // Direct3D device object
	IDirect3DSurface9 *backBuffer = nullptr;
	ID3DXSprite *spriteHandler = nullptr;    // Sprite helper library to help us draw 2D image on the screen
};