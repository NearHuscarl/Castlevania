#pragma once

#include <Windows.h>
#include "Viewport.h"
#include "../GraphicsDeviceInformation.h"
#include "../Device.h"
#include "../Base/Color.h"
#include "../Base/Rect.h"

class GraphicsDevice
{
public:
	GraphicsDevice(GraphicsDeviceInformation gdi);
	void Initialize();

	Viewport GetViewport();
	void SetViewport(Viewport viewport);

	Color GetColorKey();
	void SetColorKey(Color color);

	Rect GetDisplay();

	void Clear(Color color);

	IRenderDevice_ GetRenderDevice();
	ISurface_ GetSurface();
	ISpriteHandler_ GetSpriteHandler();

	virtual ~GraphicsDevice();

private:
	DeviceDriverType driverType;
	PresentationParameters presentationParameters;
	Viewport viewport;
	Color colorKey = Color(255, 0, 255, 255);

	IRenderDevice_ renderDevice = nullptr;    // Direct3D device object
	ISurface_ surface = nullptr;
	ISpriteHandler_ spriteHandler = nullptr;  // Sprite helper library to help us draw 2D image on the screen
};