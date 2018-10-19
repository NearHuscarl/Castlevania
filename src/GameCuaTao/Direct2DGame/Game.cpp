#include "Game.h"
#include "Utilities/TimeHelper.h"

// TODO: refactor
constexpr int MAX_FRAME_RATE = 90;
constexpr auto BACKGROUND_COLOR = D3DCOLOR_XRGB(200, 200, 255);

GameWindow &Game::GetWindow()
{
	return *window;
}

GraphicsDevice &Game::GetGraphicsDevice()
{
	return graphics->GetGraphicsDevice();
}

Game::Game(HINSTANCE hInstance)
{
	serviceProvider = std::make_shared<ServiceProvider>();
	window          = std::make_shared<GameWindow>(hInstance);
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

	LoadResources();
}

// Load all game resources
// For example: load textures, sprites, animations and mario object
void Game::LoadResources()
{
}

// Update world status for this frame
// deltaTime: time period between beginning of last frame and beginning of this frame
void Game::Update(unsigned long deltaTime)
{
}

void Game::Draw(ISpriteBatch_ spriteBatch)
{
}

// Render a frame
void Game::Render()
{
	auto renderDevice = GetGraphicsDevice().GetRenderDevice();
	auto surface = GetGraphicsDevice().GetBackBuffer();
	auto spriteBatch = GetGraphicsDevice().GetSpriteBatch();

	if (renderDevice->BeginScene())
	{
		// Clear back buffer with a color
		renderDevice->ColorFill(surface, nullptr, BACKGROUND_COLOR);

		Draw(spriteBatch);

		renderDevice->EndScene();
	}

	// Display back buffer content to the screen
	renderDevice->Present(nullptr, nullptr, nullptr, nullptr);
}

void Game::Run()
{
	auto lastTime = TimeHelper::GetTimeNow();
	auto tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (IsRunning())
	{
		auto currentTime = TimeHelper::GetTimeNow();
		auto deltaTime = currentTime - lastTime;

		if (deltaTime >= tickPerFrame)
		{
			lastTime = currentTime;

			input->ProcessKeyboard();

			Update(deltaTime);
			Render();
		}
		else
			Sleep(tickPerFrame - deltaTime);
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