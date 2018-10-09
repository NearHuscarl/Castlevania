#include "DemoGame.h"
#include "Animation/SpriteManager.h"
#include "Animation/AnimationSettings.h"
#include "Animation/Animation.h"
#include "Animation/AnimationManager.h"

// TODO: refactor
constexpr int SCREEN_WIDTH = 320;
constexpr int SCREEN_HEIGHT = 240;


DemoGame::DemoGame(HINSTANCE hInstance) : Game(hInstance)
{
	content.SetRootDirectory("Content");
	window.SetScreenWidth(900);
	window.SetScreenHeight(600);
}

void DemoGame::Initialize()
{
	Game::Initialize();
}

void DemoGame::LoadResources()
{
	AnimationManager::GetInstance()->LoadResource(&content); // Load all object animations from existed sprites

	mario = new Mario();
	mario->LoadContent(content);
}

// Update world status for this frame
// deltaTime: time period between beginning of last frame and beginning of this frame
void DemoGame::Update(unsigned long deltaTime)
{
	mario->Update(deltaTime);
}

void DemoGame::Draw(ID3DXSprite *spriteHandler)
{
	mario->Draw(spriteHandler);
}