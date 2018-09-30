//#include <d3d9.h>

#include "Game.h"
#include "Animation/TextureManager.h"
#include "Input/InputManager.h"

// TODO: refactor
#define MAX_FRAME_RATE 90
#define BACKGROUND_COLOR D3DCOLOR_XRGB(200, 200, 255)

Game::Game(HINSTANCE hInstance, int nCmdShow, int screenWidth, int screenHeight)
{
	graphics = new Graphics(hInstance, nCmdShow, screenWidth, screenHeight);
}

void Game::Initialize()
{
	graphics->InitWindow();
	graphics->InitializeDevices();

	TextureManager::GetInstance()->Initialize(graphics);
	InputManager::GetInstance()->InitKeyboard(graphics->GetWindowHandler());

	LoadResources();
}

/*
	Load all game resources
	In this example: load textures, sprites, animations and mario object
*/
void Game::LoadResources()
{
}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Game::Update(DWORD dt)
{
}

void Game::Draw()
{
}

/*
	Render a frame
*/
void Game::Render()
{
	GDevicePtr d3ddv = graphics->GetDirect3DDevice();
	GSurfacePtr bb = graphics->GetBackBuffer();
	GSpritePtr spriteHandler = graphics->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		Draw();

		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

int Game::Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;
	InputManager *inputManager = InputManager::GetInstance();

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		// TODO: change dt -> deltatime for clarity
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			inputManager->ProcessKeyboard();

			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);
	}

	return 1;
}