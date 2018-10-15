#include "Game.h"
#include "GraphicsDeviceManager.h"

// Initialize DirectX, create a Direct3D device for rendering within the window, initial Sprite library for
// rendering 2D images
// - hInst: Application instance handle
// - hWnd: Application window handle
GraphicsDeviceManager::GraphicsDeviceManager(Game *game)
{
	this->game = game;
}

void GraphicsDeviceManager::CreateDevice()
{
	auto hWnd = game->GetWindow().GetHandle();
	graphicsDevice.CreateDevice(hWnd);
}

GraphicsDevice &GraphicsDeviceManager::GetGraphicsDevice()
{
	return graphicsDevice;
}
