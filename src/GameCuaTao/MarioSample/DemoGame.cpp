#include "DemoGame.h"

DemoGame::DemoGame(HINSTANCE hInstance) : Game(hInstance)
{
	content->SetRootDirectory("MarioSample/Content");
	window->SetScreenWidth(320);
	window->SetScreenHeight(240);
}

void DemoGame::Initialize()
{
	Game::Initialize();
}

void DemoGame::LoadResources()
{
	mario = std::make_shared<Mario>();
	mario->LoadContent(*content);
}

void DemoGame::Update(unsigned long deltaTime)
{
	mario->Update(deltaTime);
}

void DemoGame::Draw(ISpriteHandler_ spriteHandler)
{
	mario->Draw(spriteHandler);
}