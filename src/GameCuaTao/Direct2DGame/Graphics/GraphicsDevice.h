#pragma once

#include <Windows.h>
#include "Viewport.h"
#include "../Device.h"
#include "../Base/Color.h"

class GraphicsDevice
{
public:
	Viewport GetViewport();
	void SetViewport(Viewport viewport);

	Color GetTransparentColor();
	void SetTransparentColor(Color color);

	void CreateDevice(HWND hWnd);
	void Clear(Color color);

	IRenderDevice_ GetRenderDevice();
	ISurface_ GetSurface();
	ISpriteHandler_ GetSpriteHandler();

	virtual ~GraphicsDevice();

private:
	Viewport viewport;
	Color transparentColor = Color(255, 255, 255);

	IRenderDevice_ renderDevice = nullptr;    // Direct3D device object
	ISurface_ surface = nullptr;
	ISpriteHandler_ spriteHandler = nullptr;  // Sprite helper library to help us draw 2D image on the screen
};