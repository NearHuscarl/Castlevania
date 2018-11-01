#include "GraphicsDevice.h"
#include "../Utilities/FileLogger.h"

// Initialize DirectX, create a Direct3D device for rendering within the window, initial Sprite library for
// rendering 2D images
// - hInst: Application instance handle
// - hWnd: Application window handle
GraphicsDevice::GraphicsDevice(GraphicsDeviceInformation gdi)
{
	presentationParameters = gdi.presentationParameters;
	driverType = gdi.driverType;
	viewport = Viewport{ 0, 0, GetDisplay().Width(), GetDisplay().Height() };

	Initialize();
}

void GraphicsDevice::Initialize()
{
	auto device = Direct3DCreate9(D3D_SDK_VERSION);
	auto deviceType = DeviceType{};

	switch (driverType)
	{
		case DeviceDriverType::Hardware:
			deviceType = D3DDEVTYPE_HAL;
			break;

		case DeviceDriverType::Reference:
			deviceType = D3DDEVTYPE_REF;
			break;

		case DeviceDriverType::Software:
			deviceType = D3DDEVTYPE_SW;
			break;
	}

	device->CreateDevice(
		D3DADAPTER_DEFAULT,                  // Use default video card
		deviceType,                          // Use the hardware renderer
		nullptr,                             // Window handle
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, // Do not use T&L (for compatibility)
		&presentationParameters,             // Presentation parameters
		&renderDevice);                      // Pointer to the new device

	if (renderDevice == nullptr)
	{
		FileLogger::GetInstance().Error("CreateDevice failed");
		return;
	}

	renderDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &surface);

	// Initialize sprite helper from Direct3DX helper library
	D3DXCreateSprite(renderDevice, &spriteHandler);

	FileLogger::GetInstance().Info("Initialize GraphicsDriver done");
}

Viewport GraphicsDevice::GetViewport()
{
	return viewport;
}

void GraphicsDevice::SetViewport(Viewport viewport)
{
	this->viewport = viewport;
}

Color GraphicsDevice::GetColorKey()
{
	return colorKey;
}

void GraphicsDevice::SetColorKey(Color color)
{
	colorKey = color;
}

Rect GraphicsDevice::GetDisplay()
{
	return Rect{ 0, 0,
		(int)presentationParameters.BackBufferWidth,
		(int)presentationParameters.BackBufferHeight };
}

void GraphicsDevice::Clear(Color color)
{
	renderDevice->ColorFill(surface, nullptr, color.Get());
}

IRenderDevice_ GraphicsDevice::GetRenderDevice()
{
	return renderDevice;
}

ISurface_ GraphicsDevice::GetSurface()
{
	return surface;
}

ISpriteHandler_ GraphicsDevice::GetSpriteHandler()
{
	return spriteHandler;
}

GraphicsDevice::~GraphicsDevice()
{
	if (spriteHandler != nullptr)
		spriteHandler->Release();

	if (surface != nullptr)
		surface->Release();

	if (renderDevice != nullptr)
		renderDevice->Release();
}
