#include "SceneManager.h"
#include "MenuScene.h"
#include "IntroScene.h"
#include "GameplayScene.h"

using namespace Castlevania;

SceneManager::SceneManager(Game &game) : game{ game }
{
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

SpriteExtensions &SceneManager::GetSpriteBatch()
{
	return *spriteBatch;
}

#pragma endregion

void SceneManager::Update(float deltaTime)
{
	if (nextScene != nullptr)
	{
		NextScene(std::move(nextScene));
	}
	currentScene->Update(deltaTime);
}

void SceneManager::Draw(GameTime gameTime)
{
	currentScene->Draw(gameTime);
}

void SceneManager::SetNextScene(Scene scene)
{
	nextScene = GetScene(scene);
	nextScene->LoadContent();
}

void SceneManager::NextScene(std::unique_ptr<AbstractScene> scene)
{
	// reassign std::unique_ptr make the old object destroyed and its memory deallocated :)
	currentScene = std::move(scene);
}

AbstractScene *SceneManager::GetCurrentScene()
{
	return currentScene.get();
}

std::unique_ptr<AbstractScene> SceneManager::GetScene(Scene scene)
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