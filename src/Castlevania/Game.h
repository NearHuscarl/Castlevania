#pragma once

#include "GameWindow.h"
#include "GraphicsDeviceManager.h"
#include "Input/InputManager.h"
#include "ContentManager.h"

class Game
{
public:
	virtual void Initialize();
	virtual void LoadResources();
	virtual void Update(unsigned long deltaTime);
	virtual void Draw(ID3DXSprite *spriteHandler);

	int Run();

	GameWindow &GetWindow();
	GraphicsDevice &GetGraphicsDevice();

protected:
	Game(HINSTANCE hInstance);

	GameWindow window;
	GraphicsDeviceManager graphics;
	InputManager *input;
	ContentManager content;

private:
	bool isRunning;
	void Render();
};