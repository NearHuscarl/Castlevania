#include "GraphicsDevice.h"
#include "Utilities/FileLogger.h"

void GraphicsDevice::CreateDevice(HWND hWnd)
{
	IDirect3D9 *d3d = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;

	RECT rectangle;
	GetClientRect(hWnd, &rectangle);	// retrieve Window width & height 

	d3dpp.BackBufferHeight = rectangle.bottom + 1;
	d3dpp.BackBufferWidth = rectangle.right + 1;

	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&device);

	if (device == nullptr)
	{
		FileLogger::GetInstance()->Error("CreateDevice failed");
		return;
	}

	device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);

	// Initialize sprite helper from Direct3DX helper library
	D3DXCreateSprite(device, &spriteHandler);

	FileLogger::GetInstance()->Info("InitGame done");
}

DevicePtr GraphicsDevice::GetDevice()
{
	return device;
}

SurfacePtr GraphicsDevice::GetBackBuffer()
{
	return backBuffer;
}

SpritePtr GraphicsDevice::GetSpriteHandler()
{
	return spriteHandler;
}

GraphicsDevice::~GraphicsDevice()
{
	if (spriteHandler != nullptr)
		spriteHandler->Release();

	if (backBuffer != nullptr)
		backBuffer->Release();

	if (device != nullptr)
		device->Release();
}
