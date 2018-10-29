#include "GraphicsDevice.h"
#include "../Utilities/FileLogger.h"

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

void GraphicsDevice::CreateDevice(HWND hWnd)
{
	auto device = Direct3DCreate9(D3D_SDK_VERSION);
	auto presentationParameters = PresentationParameters{};

	ZeroMemory(&presentationParameters, sizeof(presentationParameters));

	presentationParameters.Windowed = TRUE;
	presentationParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	presentationParameters.BackBufferFormat = D3DFMT_X8R8G8B8;
	presentationParameters.BackBufferCount = 1;

	auto rect = RECT{};
	GetClientRect(hWnd, &rect);	// retrieve Window width & height 

	presentationParameters.BackBufferHeight = rect.bottom + 1;
	presentationParameters.BackBufferWidth = rect.right + 1;

	device->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&presentationParameters,
		&renderDevice);

	if (renderDevice == nullptr)
	{
		FileLogger::GetInstance().Error("CreateDevice failed");
		return;
	}

	renderDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &surface);

	// Initialize sprite helper from Direct3DX helper library
	D3DXCreateSprite(renderDevice, &spriteHandler);

	FileLogger::GetInstance().Info("InitGame done");
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
