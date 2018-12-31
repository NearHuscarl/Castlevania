#include "SceneManager.h"
#include "MenuScene.h"
#include "GameplayScene.h"
#include "GameOverScene.h"
#include "../Utilities/DevTool.h"

using namespace Castlevania;

SceneManager::SceneManager(Game &game) : game{ game }
{
	this->nextScene = nullptr;
	this->objectFactory = std::make_unique<ObjectFactory>(GetContent());
	this->spriteBatch = std::make_unique<SpriteExtensions>(game.GetGraphicsDevice());
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

ObjectFactory &SceneManager::GetFactory()
{
	return *objectFactory;
}

SpriteExtensions &SceneManager::GetSpriteBatch()
{
	return *spriteBatch;
}

#pragma endregion

void SceneManager::Update(GameTime gameTime)
{
	DevTool::Update(*this);

	if (nextScene != nullptr)
		currentScene = std::move(nextScene);
	
	currentScene->Update(gameTime);
}

void SceneManager::Draw(GameTime gameTime)
{
	currentScene->Draw(gameTime);
}

AbstractScene &SceneManager::SetNextScene(Scene scene)
{
	nextScene = ConstructScene(scene);
	nextScene->LoadContent();
	return *nextScene;
}

std::unique_ptr<AbstractScene> SceneManager::ConstructScene(Scene scene)
{
	switch (scene)
	{
		case Scene::MENU:
			return std::make_unique<MenuScene>(*this);
		
		case Scene::GAMEPLAY:
			return std::make_unique<GameplayScene>(*this);

		case Scene::GAMEOVER:
			return std::make_unique<GameOverScene>(*this);

		default:
			throw std::invalid_argument("Bad scene choice");
	}
}