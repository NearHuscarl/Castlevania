#pragma once

#include <Windows.h>
#include "Device.h"

class GraphicsDevice
{
public:
	Color GetTransparentColor();
	void SetTransparentColor(Color color);

	void CreateDevice(HWND hWnd);

	IRenderDevice GetRenderDevice();
	ISurface GetBackBuffer();
	ISpriteHandler GetSpriteHandler();

	virtual ~GraphicsDevice();

private:
	Color transparentColor = D3DCOLOR_XRGB(255, 255, 255);

	IRenderDevice renderDevice = nullptr;       // Direct3D device object
	ISurface backBuffer = nullptr;
	ISpriteHandler spriteHandler = nullptr;    // Sprite helper library to help us draw 2D image on the screen
};