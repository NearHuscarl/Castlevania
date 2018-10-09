#include "Game.h"

// TODO: refactor
constexpr int MAX_FRAME_RATE = 90;
constexpr auto BACKGROUND_COLOR = D3DCOLOR_XRGB(200, 200, 255);

Game::Game(HINSTANCE hInstance)
{
	window = GameWindow(hInstance);
	graphics = GraphicsDeviceManager(this);
	input = InputManager::GetInstance();
	content = ContentManager(this);
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

void Game::Draw(ID3DXSprite *spriteHandler)
{
}

// Render a frame
void Game::Render()
{
	IDirect3DDevice9 *device = GetGraphicsDevice().GetDevice();
	IDirect3DSurface9 *surface = GetGraphicsDevice().GetBackBuffer();
	ID3DXSprite *spriteHandler = GetGraphicsDevice().GetSpriteHandler();

	if (device->BeginScene())
	{
		// Clear back buffer with a color
		device->ColorFill(surface, nullptr, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		Draw(spriteHandler);

		spriteHandler->End();
		device->EndScene();
	}

	// Display back buffer content to the screen
	device->Present(nullptr, nullptr, nullptr, nullptr);
}

int Game::Run()
{
	MSG msg;
	unsigned long lastTime = GetTickCount();
	unsigned long tickPerFrame = 1000 / MAX_FRAME_RATE;
	InputManager *inputManager = InputManager::GetInstance();

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

		unsigned long currentTime = GetTickCount();
		unsigned long deltaTime = currentTime - lastTime;

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
