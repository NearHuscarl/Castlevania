#pragma once

#include "GraphicsDevice.h"

class Game;

class GraphicsDeviceManager
{
public:
	GraphicsDeviceManager(std::shared_ptr<Game> game);
	
	void CreateDevice();
	GraphicsDevice &GetGraphicsDevice();
	int GetFramePerSecond();

private:
	std::shared_ptr<Game> game;
	std::shared_ptr<GraphicsDevice> graphicsDevice;
	
	int framePerSecond = 90;
};