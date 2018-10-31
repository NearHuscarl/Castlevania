#pragma once

#include "Graphics/GraphicsDevice.h"

class Game;

class GraphicsDeviceManager
{
public:
	GraphicsDeviceManager(Game &game);

	static const int DefaultBackbufferWidth = 800;
	static const int DefaultBackbufferHeight = 600;

	int GetBackBufferWidth();
	void SetBackBufferWidth(int width);
	int GetBackBufferHeight();
	void SetBackBufferHeight(int height);
	
	void CreateDevice();
	GraphicsDevice &GetGraphicsDevice();
	
	int GetFramePerSecond();
	int GetTickPerFrame();

private:
	bool initialized = false;

	Game &game;
	std::shared_ptr<GraphicsDevice> graphicsDevice;
	
	bool isFullScreen;
	SurfaceFormat backBufferFormat;
	unsigned int backBufferCount;
	unsigned int backBufferWidth;
	unsigned int backBufferHeight;
	SwapEffect swapEffect;
	
	int framePerSecond;
	int tickPerFrame;

	void Initialize();

	void PreparePresentationParameters(PresentationParameters &pp);
	void PrepareGraphicsDeviceInformation(GraphicsDeviceInformation &gdi);
};