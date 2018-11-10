#include "SceneManager.h"
#include "MenuScene.h"
#include "IntroScene.h"
#include "GameplayScene.h"

using namespace Castlevania;

SceneManager::SceneManager(Game &game) : game{ game }
{
	this->spriteBatch = std::make_unique<SpriteExtensions>(game.GetGraphicsDevice());
	this->stageManager = std::make_unique<StageManager>();
	this->nextScene = nullptr;

	this->stageManager->LoadContent(game.GetContent());
}

#pragma region Getters

GraphicsDevice &SceneManager::GetGraphicsDevice()
{
	return game.GetGraphicsDevice();
}

ContentManager &SceneManager::GetContent()
{
	return game.GetContent();
}

SpriteExtensions &SceneManager::GetSpriteBatch()
{
	return *spriteBatch;
}

StageManager &SceneManager::GetStageManager()
{
	return *stageManager;
}

#pragma endregion

void SceneManager::Update(float deltaTime)
{
	if (nextScene != nullptr)
	{
		// reassign std::unique_ptr make the old object destroyed
		// and its memory deallocated automatically :)
		currentScene = std::move(nextScene);
	}
	currentScene->Update(deltaTime);
}

void SceneManager::Draw(GameTime gameTime)
{
	currentScene->Draw(gameTime);
}

void SceneManager::SetNextScene(Scene scene)
{
	nextScene = ConstructScene(scene);
	nextScene->LoadContent();
}

std::unique_ptr<AbstractScene> SceneManager::ConstructScene(Scene scene)
{
	switch (scene)
	{
		case Scene::MENU:
			return std::make_unique<MenuScene>(*this);
		
		case Scene::INTRO:
			return std::make_unique<IntroScene>(*this);
		
		case Scene::GAMEPLAY:
			return std::make_unique<GameplayScene>(*this);

		default:
			throw std::invalid_argument("Bad scene choice");
	}
}