#pragma once

#include <Windows.h>
#include "Viewport.h"
#include "../Device.h"
#include "../Base/Color.h"
#include "../Base/Rect.h"

class GraphicsDevice
{
public:
	Viewport GetViewport();
	void SetViewport(Viewport viewport);

	Color GetColorKey();
	void SetColorKey(Color color);

	Rect GetDisplay();

	void CreateDevice(HWND hWnd);
	void Clear(Color color);

	IRenderDevice_ GetRenderDevice();
	ISurface_ GetSurface();
	ISpriteHandler_ GetSpriteHandler();

	virtual ~GraphicsDevice();

private:
	Viewport viewport;
	Color colorKey = Color(255, 0, 255, 255);
	Rect display;

	IRenderDevice_ renderDevice = nullptr;    // Direct3D device object
	ISurface_ surface = nullptr;
	ISpriteHandler_ spriteHandler = nullptr;  // Sprite helper library to help us draw 2D image on the screen
};