#include "DemoGame.h"
#include "Animation/TextureManager.h"
#include "Animation/SpriteManager.h"
#include "Animation/AnimationSettings.h"
#include "Animation/Animation.h"
#include "Animation/AnimationManager.h"

// TODO: refactor
constexpr int SCREEN_WIDTH = 320;
constexpr int SCREEN_HEIGHT = 240;


DemoGame::DemoGame(HINSTANCE hInstance, int nCmdShow) : Game(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT)
{
	content.SetRootDirectory("Content");
	graphics.SetTransparentColor(D3DCOLOR_RGBA(255, 0, 255, 255));
}

void DemoGame::Initialize()
{
	Game::Initialize();
}

void DemoGame::LoadResources()
{
	TextureManager::GetInstance()->LoadResource(); // Load all spritesheets
	SpriteManager::GetInstance()->LoadResource(); // Load individual sprites from spritesheets
	AnimationManager::GetInstance()->LoadResource(); // Load all object animations from existed sprites

	mario = new Mario();
	mario->LoadContent();
}

// Update world status for this frame
// dt: time period between beginning of last frame and beginning of this frame
void DemoGame::Update(unsigned long dt)
{
	mario->Update(dt);
}

void DemoGame::Draw()
{
	mario->Render();
}