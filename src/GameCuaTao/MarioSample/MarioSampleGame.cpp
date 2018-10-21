#include "MarioSampleGame.h"
#include "Direct2DGame/Utilities/AudioManager.h"

using namespace MarioSample;

MarioSampleGame::MarioSampleGame()
{
	content->SetRootDirectory("MarioSample/Content");
	window->SetScreenWidth(320);
	window->SetScreenHeight(240);
}

void MarioSampleGame::Initialize()
{
	Game::Initialize();
}

void MarioSampleGame::LoadResources()
{
	AudioManager::LoadResource(*content, { "Jump", "Overworld" });
	helpText = content->Load<SpriteFont>("Roboto-Bold.ttf");
	mario = std::make_shared<Mario>();
	mario->LoadContent(*content);

	AudioManager::PlaySong("Overworld");
}

void MarioSampleGame::Update(GameTime gameTime)
{
	auto deltaTime = gameTime.ElapsedGameTime.Milliseconds();

	mario->Update(deltaTime);
}

void MarioSampleGame::Draw(ISpriteBatch_ spriteBatch)
{
	spriteBatch->Begin(D3DXSPRITE_ALPHABLEND);

	mario->Draw(spriteBatch);
	helpText->Draw(spriteBatch, "Press arrow keys to move", Vector(30, 30), Color(255, 0, 255));

	spriteBatch->End();
}