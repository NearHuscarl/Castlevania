#include "CastlevaniaGame.h"
#include "Scenes/MenuScene.h"
#include "Utilities/AudioManager.h"
#include "Utilities/Audio.h"

using namespace Castlevania;

Castlevania::CastlevaniaGame::CastlevaniaGame()
{
	content->SetRootDirectory("Castlevania/Content");

	window->SetScreenWidth(640);
	window->SetScreenHeight(480);
}

void CastlevaniaGame::Initialize()
{
	Game::Initialize();

	sceneManager = std::make_unique<SceneManager>(content);
	sceneManager->NextScene(Scene::MENU);
}

void CastlevaniaGame::LoadContent()
{
	spriteBatch = std::make_unique<SpriteBatch>(GetGraphicsDevice());

	AudioManager::LoadContent(*content, GAME_AUDIO);
}

void CastlevaniaGame::Update(GameTime gameTime)
{
	auto deltaTime = (float)gameTime.ElapsedGameTime.Milliseconds();

	sceneManager->Update(deltaTime);
}

void CastlevaniaGame::Draw(GameTime gameTime)
{
	spriteBatch->GetSpriteHandler()->Begin(D3DXSPRITE_ALPHABLEND);

	sceneManager->Draw(*spriteBatch);

	spriteBatch->GetSpriteHandler()->End();
}