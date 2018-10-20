#include "DemoGame.h"
#include "Direct2DGame/Utilities/AudioManager.h"

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
	AudioManager::LoadResource(*content, { "Jump", "Overworld" });
	helpText = content->Load<SpriteFont>("Roboto-Bold.ttf");
	mario = std::make_shared<Mario>();
	mario->LoadContent(*content);

	AudioManager::PlaySong("Overworld");
}

void DemoGame::Update(unsigned long deltaTime)
{
	mario->Update(deltaTime);
}

void DemoGame::Draw(ISpriteBatch_ spriteBatch)
{
	spriteBatch->Begin(D3DXSPRITE_ALPHABLEND);

	mario->Draw(spriteBatch);
	helpText->Draw(spriteBatch, "Press arrow keys to move", Vector(30, 30), Color(255, 0, 255));

	spriteBatch->End();
}