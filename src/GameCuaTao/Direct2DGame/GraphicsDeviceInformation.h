#pragma once

#include "Direct3D9.h"
#include "Graphics/DeviceDriverType.h"

struct GraphicsDeviceInformation
{
	DeviceDriverType driverType;
	PresentationParameters presentationParameters;
};