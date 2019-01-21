#include "Direct2DGame/Input/InputHelper.h"
#include "CastlevaniaGame.h"
#include "Utilities/AudioManager.h"

using namespace Castlevania;

CastlevaniaGame::CastlevaniaGame()
{
	content->SetRootDirectory("Castlevania/Content");

	graphics->SetBackBufferWidth(512);
	graphics->SetBackBufferHeight(448);

	window->SetTitle("Castlevania NES");
}

void CastlevaniaGame::Initialize()
{
	Game::Initialize();

	sceneManager = std::make_unique<SceneManager>(*this);
	sceneManager->SetNextScene(Scene::MENU);
}

void CastlevaniaGame::LoadContent()
{
	AudioManager::LoadContent(*content);
}

void CastlevaniaGame::Update(GameTime gameTime)
{
	InputHelper::Update();
	sceneManager->Update(gameTime);
}

void CastlevaniaGame::Draw(GameTime gameTime)
{
	GetGraphicsDevice().Clear(Color::Black());

	sceneManager->Draw(gameTime);
}