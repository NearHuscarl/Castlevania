#include "Game.h"

GameWindow &Game::GetWindow()
{
	return *window;
}

GraphicsDevice &Game::GetGraphicsDevice()
{
	return graphics->GetGraphicsDevice();
}

GraphicsDeviceManager &Game::GetGraphicsDeviceManager()
{
	return *graphics;
}

ContentManager &Game::GetContent()
{
	return *content;
}

Game::Game()
{
	service  = std::make_shared<ServiceProvider>();
	window   = std::make_unique<GameWindow>(*this);
	graphics = std::make_unique<GraphicsDeviceManager>(*this);
	content  = std::make_unique<ContentManager>(service);
	gameInput = std::make_unique<GameInput>();

	service->Add<GraphicsDeviceManager>(graphics.get());
	service->Add<GameWindow>(&GetWindow());
}

void Game::Initialize()
{
	graphics->CreateDevice();
	gameInput->Initialize(window->GetHandle());

	LoadContent();
}

// Load all game resources
// For example: load textures, sprites, animations and mario object
void Game::LoadContent()
{
}

// Update world status for this frame
// deltaTime: time period between beginning of last frame and beginning of this frame
void Game::Update(GameTime gameTime)
{
}

void Game::Draw(GameTime gameTime)
{
}

// Render a frame
void Game::Render(GameTime gameTime)
{
	auto renderDevice = GetGraphicsDevice().GetRenderDevice();

	if (renderDevice->BeginScene())
	{
		Draw(gameTime);
		renderDevice->EndScene();
	}

	// Display back buffer content to the screen
	renderDevice->Present(nullptr, nullptr, nullptr, nullptr);
}

void Game::Run()
{
	if (!initialized)
	{
		Initialize();
		initialized = false;
	}
	
	gameTimer.Start();
	while (ProcessEvents())
	{
		Tick();
		auto deltaTime = (int)gameTime.ElapsedGameTime.Milliseconds();
		auto tickPerFrame = (int)graphics->GetTickPerFrame();

		if (deltaTime >= tickPerFrame)
		{
			gameInput->Update();
			Update(gameTime);
			Render(gameTime);
		}
		else
			Sleep(tickPerFrame - deltaTime);
	}
}

bool Game::ProcessEvents()
{
	auto msg = MSG{};

	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
			return false;

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return true;
}

void Game::Tick()
{
	auto currentTick = gameTimer.ElapsedMilliseconds();
	auto accumulatedTime = TimeSpan::FromMilliseconds(currentTick - gameTime.GetPreviousTicks());

	gameTime.SetPreviousTicks(currentTick);
	gameTime.ElapsedGameTime = accumulatedTime;
	gameTime.TotalGameTime += accumulatedTime;
}
