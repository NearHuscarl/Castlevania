#pragma once

#include "GameWindow.h"
#include "GameTime.h"
#include "GraphicsDeviceManager.h"
#include "Content/ContentManager.h"
#include "ServiceProvider.h"

class Game
{
public:
	GameWindow &GetWindow();
	GraphicsDevice &GetGraphicsDevice();
	ContentManager &GetContent();

	virtual void LoadContent();
	virtual void Update(GameTime gameTime);
	virtual void Draw(GameTime gameTime);

	void Run();

	virtual ~Game();

protected:
	Game();

	virtual void Initialize();

	std::shared_ptr<GameWindow> window;
	std::shared_ptr<GraphicsDeviceManager> graphics;
	std::shared_ptr<ContentManager> content;
	std::shared_ptr<ServiceProvider> serviceProvider;

private:
	bool initialized = false;
	GameTime gameTime;

	bool IsRunning();
	void Render(GameTime gameTime);
	
	double GetTickPerFrame();
	void Tick();
};