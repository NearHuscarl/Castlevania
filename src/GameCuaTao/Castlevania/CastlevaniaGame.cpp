#include "CastlevaniaGame.h"
#include "Scenes/MenuScene.h"
#include "Settings/Fonts.h"
#include "Utilities/AudioManager.h"
#include "Settings/Audios.h"

using namespace Castlevania;

CastlevaniaGame::CastlevaniaGame()
{
	content->SetRootDirectory("Castlevania/Content");

	window->Width(529);
	window->Height(485);
}

void CastlevaniaGame::Initialize()
{
	Game::Initialize();

	sceneManager = std::make_unique<SceneManager>(*this);
	sceneManager->NextScene(Scene::MENU);
}

void CastlevaniaGame::LoadContent()
{
	Fonts::LoadContent(*content);
	AudioManager::LoadContent(*content, GAME_AUDIO);
}

void CastlevaniaGame::Update(GameTime gameTime)
{
	auto deltaTime = (float)gameTime.ElapsedGameTime.Milliseconds();

	sceneManager->Update(deltaTime);
}

void CastlevaniaGame::Draw(GameTime gameTime)
{
	GetGraphicsDevice().Clear(Color::LavenderBlue());

	sceneManager->Draw(gameTime);
}