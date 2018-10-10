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
		&d3ddv);

	if (d3ddv == nullptr)
	{
		FileLogger::GetInstance()->Error("CreateDevice failed");
		return;
	}

	d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);

	// Initialize sprite helper from Direct3DX helper library
	D3DXCreateSprite(d3ddv, &spriteHandler);

	FileLogger::GetInstance()->Info("InitGame done");
}

IDirect3DDevice9 *GraphicsDevice::GetDevice()
{
	return d3ddv;
}

IDirect3DSurface9 *GraphicsDevice::GetBackBuffer()
{
	return backBuffer;
}

ID3DXSprite *GraphicsDevice::GetSpriteHandler()
{
	return spriteHandler;
}

GraphicsDevice::~GraphicsDevice()
{
	if (spriteHandler != nullptr)
		spriteHandler->Release();

	if (backBuffer != nullptr)
		backBuffer->Release();

	if (d3ddv != nullptr)
		d3ddv->Release();
}
