#include "Game.h"
#include "GraphicsDeviceManager.h"

// Initialize DirectX, create a Direct3D device for rendering within the window, initial Sprite library for
// rendering 2D images
// - hInst: Application instance handle
// - hWnd: Application window handle
GraphicsDeviceManager::GraphicsDeviceManager(std::shared_ptr<Game> game)
{
	this->game = game;
	this->graphicsDevice = std::make_shared<GraphicsDevice>();
}

void GraphicsDeviceManager::CreateDevice()
{
	auto window = game->GetWindow();
	auto hWnd = window.GetHandle();
	auto viewport = Viewport{ 0, 0, window.Width(), window.Height() };
	
	graphicsDevice->CreateDevice(hWnd);
	graphicsDevice->SetViewport(viewport);
}

GraphicsDevice &GraphicsDeviceManager::GetGraphicsDevice()
{
	return *graphicsDevice;
}

int GraphicsDeviceManager::GetFramePerSecond()
{
	return framePerSecond;
}
