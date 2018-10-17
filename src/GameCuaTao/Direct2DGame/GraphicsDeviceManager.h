#pragma once

#include "GraphicsDevice.h"

class Game;

class GraphicsDeviceManager
{
public:
	GraphicsDeviceManager(std::shared_ptr<Game> game);
	
	void CreateDevice();
	GraphicsDevice &GetGraphicsDevice();

private:
	std::shared_ptr<Game> game;
	std::shared_ptr<GraphicsDevice> graphicsDevice;
	
	int frameRate;
};