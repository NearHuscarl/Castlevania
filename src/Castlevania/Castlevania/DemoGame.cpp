#include "DemoGame.h"

DemoGame::DemoGame(HINSTANCE hInstance) : Game(hInstance)
{
	content.SetRootDirectory("Castlevania\\Content");
	window.SetScreenWidth(640);
	window.SetScreenHeight(480);
}

void DemoGame::Initialize()
{
	Game::Initialize();
}

void DemoGame::LoadResources()
{
	mario = new Mario();
	mario->LoadContent(content);
}

// Update world status for this frame
// deltaTime: time period between beginning of last frame and beginning of this frame
void DemoGame::Update(unsigned long deltaTime)
{
	mario->Update(deltaTime);
}

void DemoGame::Draw(SpritePtr spriteHandler)
{
	mario->Draw(spriteHandler);
}