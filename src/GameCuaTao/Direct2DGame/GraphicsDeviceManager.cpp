#include "Game.h"
#include "GraphicsDeviceManager.h"

GraphicsDeviceManager::GraphicsDeviceManager(Game &game) : game{ game }
{
	// TODO: refactor
	framePerSecond = 90;
	tickPerFrame = 1000 / framePerSecond;

	isFullScreen = false;                       // Set to true for windowed mode, false for fullscreen mode
	backBufferFormat = D3DFMT_X8R8G8B8;         // Format of the back buffer, D3DFORMAT
	backBufferCount = 1;                        // Number of back buffers. 1 is double buffering
	swapEffect = D3DSWAPEFFECT_DISCARD;         // Swapping method for back buffer
	backBufferWidth = DefaultBackbufferWidth;   // Width of back buffer
	backBufferHeight = DefaultBackbufferHeight; // Height of back buffer
}

int GraphicsDeviceManager::GetBackBufferWidth()
{
	return backBufferWidth;
}

void GraphicsDeviceManager::SetBackBufferWidth(int width)
{
	backBufferWidth = width;
}

int GraphicsDeviceManager::GetBackBufferHeight()
{
	return backBufferHeight;
}

void GraphicsDeviceManager::SetBackBufferHeight(int height)
{
	backBufferHeight = height;
}

void GraphicsDeviceManager::CreateDevice()
{
	if (!initialized)
	{
		Initialize();
		initialized = true;
	}

	auto gdi = GraphicsDeviceInformation{};
	PrepareGraphicsDeviceInformation(gdi);
	graphicsDevice = std::make_unique<GraphicsDevice>(gdi);
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

void GraphicsDeviceManager::Initialize()
{
	game.GetWindow().Create();
}

void GraphicsDeviceManager::PreparePresentationParameters(PresentationParameters &presentationParameters)
{
	presentationParameters.hDeviceWindow = game.GetWindow().GetHandle();
	presentationParameters.Windowed = isFullScreen ? false : true;
	presentationParameters.BackBufferFormat = backBufferFormat;
	presentationParameters.BackBufferCount = backBufferCount;
	presentationParameters.BackBufferWidth = backBufferWidth;
	presentationParameters.BackBufferHeight = backBufferHeight;
	presentationParameters.SwapEffect = swapEffect;
}

void GraphicsDeviceManager::PrepareGraphicsDeviceInformation(GraphicsDeviceInformation &gdi)
{
	auto pp = PresentationParameters{};
	ZeroMemory(&pp, sizeof(pp));
	
	PreparePresentationParameters(pp);
	
	gdi.presentationParameters = pp;
	gdi.driverType = DeviceDriverType::Hardware;
}