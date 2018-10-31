#pragma once

#include "Device.h"
#include "Graphics/DeviceDriverType.h"

struct GraphicsDeviceInformation
{
	DeviceDriverType driverType;
	PresentationParameters presentationParameters;
};