//#include <d3d9.h>

#include "Game.h"
#include "Content.h"
#include "Utilities/Time.h"
#include "Animation/SpriteManager.h"
#include "Animation/DxTextureManager.h"
#include "Input/InputManager.h"

// TODO: refactor
constexpr int MAX_FRAME_RATE = 90;
constexpr auto BACKGROUND_COLOR = D3DCOLOR_XRGB(200, 200, 255);

Game::Game(HINSTANCE hInstance, int nCmdShow, int screenWidth, int screenHeight)
{
	graphics = Graphics(hInstance, nCmdShow, screenWidth, screenHeight);
	content = Content(&graphics);
}

void Game::Initialize()
{
	graphics.Initialize();

	InputManager::GetInstance()->InitKeyboard(graphics.GetWindowHandler());
	DxTextureManager::Initialize(graphics.GetDirect3DDevice());
	Sprite::Initialize(&graphics);

	LoadResources();

	isRunning = true;
}

// Load all game resources
// In this example: load textures, sprites, animations and mario object
void Game::LoadResources()
{
}

// Update world status for this frame
// dt: time period between beginning of last frame and beginning of this frame
void Game::Update(unsigned long dt)
{
}

void Game::Draw()
{
}

// Render a frame
void Game::Render()
{
	GDevicePtr d3ddv = graphics.GetDirect3DDevice();
	GSurfacePtr bb = graphics.GetBackBuffer();
	GSpritePtr spriteHandler = graphics.GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, nullptr, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		Draw();

		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(nullptr, nullptr, nullptr, nullptr);
}

int Game::Run()
{
	MSG msg;
	unsigned long lastTime = GetTickCount();
	unsigned long tickPerFrame = 1000 / MAX_FRAME_RATE;
	InputManager *inputManager = InputManager::GetInstance();

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