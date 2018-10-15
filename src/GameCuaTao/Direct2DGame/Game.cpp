#include "Game.h"
#include "Utilities/TimeHelper.h"

// TODO: refactor
constexpr int MAX_FRAME_RATE = 90;
constexpr auto BACKGROUND_COLOR = D3DCOLOR_XRGB(200, 200, 255);

Game::Game(HINSTANCE hInstance) :
	window(hInstance),
	graphics(this),
	input(InputManager::GetInstance()),
	content(serviceProvider)
{
	serviceProvider.Add<GraphicsDevice>(&GetGraphicsDevice());
}

void Game::Initialize()
{
	window.Create();
	graphics.CreateDevice();
	input->InitKeyboard(window.GetHandle());

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

void Game::Draw(ISpriteHandler spriteHandler)
{
}

// Render a frame
void Game::Render()
{
	auto renderDevice = GetGraphicsDevice().GetRenderDevice();
	auto surface = GetGraphicsDevice().GetBackBuffer();
	auto spriteHandler = GetGraphicsDevice().GetSpriteHandler();

	if (renderDevice->BeginScene())
	{
		// Clear back buffer with a color
		renderDevice->ColorFill(surface, nullptr, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		Draw(spriteHandler);

		spriteHandler->End();
		renderDevice->EndScene();
	}

	// Display back buffer content to the screen
	renderDevice->Present(nullptr, nullptr, nullptr, nullptr);
}

int Game::Run()
{
	auto msg = MSG{};
	auto lastTime = TimeHelper::GetTimeNow();
	auto tickPerFrame = 1000 / MAX_FRAME_RATE;
	auto inputManager = InputManager::GetInstance();

	isRunning = true;
	while (isRunning)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				isRunning = false;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		auto currentTime = TimeHelper::GetTimeNow();
		auto deltaTime = currentTime - lastTime;

		if (deltaTime >= tickPerFrame)
		{
			lastTime = currentTime;

			inputManager->ProcessKeyboard();

			Update(deltaTime);
			Render();
		}
		else
			Sleep(tickPerFrame - deltaTime);
	}

	return 1;
}

GameWindow &Game::GetWindow()
{
	return window;
}

GraphicsDevice &Game::GetGraphicsDevice()
{
	return graphics.GetGraphicsDevice();
}
