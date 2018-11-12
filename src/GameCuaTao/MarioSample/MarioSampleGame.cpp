#include "MarioSampleGame.h"
#include "Direct2DGame/Input/InputHelper.h"
#include "Utilities/AudioManager.h"

using namespace MarioSample;

MarioSampleGame::MarioSampleGame()
{
	content->SetRootDirectory("MarioSample/Content");

	graphics->SetBackBufferWidth(320);
	graphics->SetBackBufferHeight(240);
}

void MarioSampleGame::Initialize()
{
	Game::Initialize();
	InputHelper::Initialize(keyboard.get());
}

void MarioSampleGame::LoadContent()
{
	spriteBatch = std::make_unique<SpriteBatch>(GetGraphicsDevice());

	AudioManager::LoadContent(*content, { "Jump", "Overworld" });
	gameFont = content->Load<SpriteFont>("Roboto");
	mario = std::make_shared<Mario>();
	mario->LoadContent(*content);

	AudioManager::PlaySong("Overworld");
}

void MarioSampleGame::Update(GameTime gameTime)
{
	auto deltaTime = (float)gameTime.ElapsedGameTime.Seconds();

	InputHelper::Update();
	mario->Update(deltaTime);
}

void MarioSampleGame::Draw(GameTime gameTime)
{
	GetGraphicsDevice().Clear(Color::LavenderBlue());

	spriteBatch->Begin(D3DXSPRITE_ALPHABLEND);

	mario->Draw(*spriteBatch);
	spriteBatch->DrawString(*gameFont, "Press arrow keys to move", Vector2{ 30, 30 }, Color{ 255, 0, 255 });

	spriteBatch->End();
}