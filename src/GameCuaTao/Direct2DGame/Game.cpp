#include "Game.h"
#include "Utilities/TimeHelper.h"

GameWindow &Game::GetWindow()
{
	return *window;
}

GraphicsDevice &Game::GetGraphicsDevice()
{
	return graphics->GetGraphicsDevice();
}

ContentManager &Game::GetContent()
{
	return *content;
}

Game::Game()
{
	serviceProvider = std::make_shared<ServiceProvider>();
	window          = std::make_shared<GameWindow>();
	graphics        = std::make_shared<GraphicsDeviceManager>(std::shared_ptr<Game>{this});
	input           = std::shared_ptr<InputManager>{ &InputManager::GetInstance() };
	content         = std::make_shared<ContentManager>(serviceProvider);

	serviceProvider->Add<GraphicsDevice>(GetGraphicsDevice());
	serviceProvider->Add<GameWindow>(GetWindow());
}

void Game::Initialize()
{
	window->Create();
	graphics->CreateDevice();
	input->InitKeyboard(window->GetHandle());

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
	auto surface = GetGraphicsDevice().GetSurface();
	auto spriteBatch = GetGraphicsDevice().GetSpriteHandler();

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

	while (IsRunning())
	{
		Tick();
		auto deltaTime = gameTime.ElapsedGameTime.Milliseconds();

		if (deltaTime >= GetTickPerFrame())
		{
			input->ProcessKeyboard();

			Update(gameTime);
			Render(gameTime);
		}
		else
			Sleep(GetTickPerFrame() - deltaTime);
	}
}

bool Game::IsRunning()
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

double Game::GetTickPerFrame()
{
	return 1000 / graphics->GetFramePerSecond();
}

void Game::Tick()
{
	auto currentTick = TimeHelper::GetTickNow();
	auto accumulatedTime = TimeSpan::FromMilliseconds(currentTick - gameTime.GetPreviousTicks());

	gameTime.SetPreviousTicks(currentTick);
	gameTime.ElapsedGameTime = accumulatedTime;
	gameTime.TotalGameTime += accumulatedTime;
}