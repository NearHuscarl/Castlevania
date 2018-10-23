#pragma once

#include <Windows.h>
#include "Device.h"
#include "Base/Color.h"

class GraphicsDevice
{
public:
	Color GetTransparentColor();
	void SetTransparentColor(Color color);

	void CreateDevice(HWND hWnd);

	IRenderDevice_ GetRenderDevice();
	ISurface_ GetBackBuffer();
	ISpriteHandler_ GetSpriteHandler();

	virtual ~GraphicsDevice();

private:
	Color transparentColor = Color(255, 255, 255);

	IRenderDevice_ renderDevice = nullptr;  // Direct3D device object
	ISurface_ backBuffer = nullptr;
	ISpriteHandler_ spriteHandler = nullptr;    // Sprite helper library to help us draw 2D image on the screen
};