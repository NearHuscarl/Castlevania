#pragma once

#include "GameWindow.h"
#include "GameTime.h"
#include "GraphicsDeviceManager.h"
#include "Input/InputManager.h"
#include "Content/ContentManager.h"
#include "ServiceProvider.h"

class Game
{
public:
	GameWindow &GetWindow();
	GraphicsDevice &GetGraphicsDevice();

	virtual void LoadResources();
	virtual void Update(GameTime gameTime);
	virtual void Draw(ISpriteBatch_ spriteBatch);

	void Run();

protected:
	Game();

	virtual void Initialize();

	std::shared_ptr<GameWindow> window;
	std::shared_ptr<GraphicsDeviceManager> graphics;
	std::shared_ptr<InputManager> input;
	std::shared_ptr<ContentManager> content;
	std::shared_ptr<ServiceProvider> serviceProvider;

private:
	bool initialized = false;
	GameTime gameTime;

	bool IsRunning();
	void Render();
	
	double GetTickPerFrame();
	void Tick();
};