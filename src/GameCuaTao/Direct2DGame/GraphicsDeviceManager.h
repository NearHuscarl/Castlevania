#pragma once

#include "Graphics/GraphicsDevice.h"

class Game;

class GraphicsDeviceManager
{
public:
	GraphicsDeviceManager(Game &game);
	
	void CreateDevice();
	GraphicsDevice &GetGraphicsDevice();
	
	int GetFramePerSecond();
	int GetTickPerFrame();

private:
	Game &game;
	std::shared_ptr<GraphicsDevice> graphicsDevice;
	
	int framePerSecond;
	int tickPerFrame;
};