#include "DemoGame.h"

DemoGame::DemoGame(HINSTANCE hInstance) : Game(hInstance)
{
	content.SetRootDirectory("MarioSample/Content");
	window.SetScreenWidth(320);
	window.SetScreenHeight(240);
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

void DemoGame::Draw(ISpriteHandler spriteHandler)
{
	mario->Draw(spriteHandler);
}