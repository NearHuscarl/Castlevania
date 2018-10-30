#include "Game.h"
#include "GraphicsDeviceManager.h"

// Initialize DirectX, create a Direct3D device for rendering within the window, initial Sprite library for
// rendering 2D images
// - hInst: Application instance handle
// - hWnd: Application window handle
GraphicsDeviceManager::GraphicsDeviceManager(Game &game) : game(game)
{
	this->graphicsDevice = std::make_shared<GraphicsDevice>();
	this->framePerSecond = 90;
	this->tickPerFrame = 1000 / framePerSecond;
}

void GraphicsDeviceManager::CreateDevice()
{
	auto hWnd = game.GetWindow().GetHandle();
	graphicsDevice->CreateDevice(hWnd);
	
	auto display = graphicsDevice->GetDisplay();
	auto viewport = Viewport{ 0, 0, display.Width(), display.Height() };
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

int GraphicsDeviceManager::GetTickPerFrame()
{
	return tickPerFrame;
}
