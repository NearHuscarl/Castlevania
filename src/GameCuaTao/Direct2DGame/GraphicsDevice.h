#pragma once

#include <Windows.h>
// TODO: #include "Device.h"
#include "Content/Content.h"

class GraphicsDevice
{
public:
	D3DCOLOR GetTransparentColor() { return transparentColor; }
	void SetTransparentColor(D3DCOLOR color) { transparentColor = color; }

	void CreateDevice(HWND hWnd);

	DevicePtr GetDevice();
	SurfacePtr GetBackBuffer();
	SpritePtr GetSpriteHandler();

	virtual ~GraphicsDevice();

private:
	D3DCOLOR transparentColor = D3DCOLOR_XRGB(255, 255, 255);

	DevicePtr device = nullptr;       // Direct3D device object
	SurfacePtr backBuffer = nullptr;
	SpritePtr spriteHandler = nullptr;    // Sprite helper library to help us draw 2D image on the screen
};