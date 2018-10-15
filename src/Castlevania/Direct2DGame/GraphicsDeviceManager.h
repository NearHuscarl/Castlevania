#pragma once

#include "GraphicsDevice.h"

class Game;

class GraphicsDeviceManager
{
public:
	GraphicsDeviceManager(Game *game);
	
	void CreateDevice();
	GraphicsDevice &GetGraphicsDevice();

private:
	Game *game;
	int frameRate;

	GraphicsDevice graphicsDevice;
};