#pragma once

#include "GameWindow.h"
#include "GameTime.h"
#include "GraphicsDeviceManager.h"
#include "Content/ContentManager.h"
#include "ServiceProvider.h"
#include "Input/GameInput.h"
#include "Utilities/Stopwatch.h"

class Game
{
public:
	GameWindow &GetWindow();
	GraphicsDevice &GetGraphicsDevice();
	GraphicsDeviceManager &GetGraphicsDeviceManager();
	ContentManager &GetContent();

	virtual void LoadContent();
	virtual void Update(GameTime gameTime);
	virtual void Draw(GameTime gameTime);

	void Run();

protected:
	Game();

	virtual void Initialize();

	std::unique_ptr<GameWindow> window;
	std::unique_ptr<GraphicsDeviceManager> graphics;
	std::unique_ptr<ContentManager> content;
	std::shared_ptr<ServiceProvider> service;
	std::unique_ptr<GameInput> gameInput;

private:
	bool initialized = false;

	GameTime gameTime;
	Stopwatch gameTimer;

	bool ProcessEvents();
	void Render(GameTime gameTime);
	
	void Tick();
};