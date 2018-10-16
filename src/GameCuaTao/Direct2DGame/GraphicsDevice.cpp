#include "GraphicsDevice.h"
#include "Utilities/FileLogger.h"

Color GraphicsDevice::GetTransparentColor()
{
	return transparentColor;
}

void GraphicsDevice::SetTransparentColor(Color color)
{
	transparentColor = color;
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

	auto rectangle = RECT{};
	GetClientRect(hWnd, &rectangle);	// retrieve Window width & height 

	presentationParameters.BackBufferHeight = rectangle.bottom + 1;
	presentationParameters.BackBufferWidth = rectangle.right + 1;

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

	renderDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);

	// Initialize sprite helper from Direct3DX helper library
	D3DXCreateSprite(renderDevice, &spriteHandler);

	FileLogger::GetInstance().Info("InitGame done");
}

IRenderDevice_ GraphicsDevice::GetRenderDevice()
{
	return renderDevice;
}

ISurface_ GraphicsDevice::GetBackBuffer()
{
	return backBuffer;
}

ISpriteHandler_ GraphicsDevice::GetSpriteHandler()
{
	return spriteHandler;
}

GraphicsDevice::~GraphicsDevice()
{
	if (spriteHandler != nullptr)
		spriteHandler->Release();

	if (backBuffer != nullptr)
		backBuffer->Release();

	if (renderDevice != nullptr)
		renderDevice->Release();
}
