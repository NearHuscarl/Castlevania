#include "SceneManager.h"
#include "MenuScene.h"
#include "IntroScene.h"
#include "GameplayScene.h"

using namespace Castlevania;

SceneManager::SceneManager(Game &game) : game(game)
{
	this->spriteBatch = std::make_unique<SpriteBatch>(game.GetGraphicsDevice());
}

GraphicsDevice &SceneManager::GetGraphicsDevice()
{
	return game.GetGraphicsDevice();
}

ContentManager &SceneManager::GetContent()
{
	return game.GetContent();
}

SpriteBatch &SceneManager::GetSpriteBatch()
{
	return *spriteBatch;
}

void SceneManager::Update(float deltaTime)
{
	currentScene->Update(deltaTime);
}

void SceneManager::Draw(GameTime gameTime)
{
	currentScene->Draw(gameTime);
}

void SceneManager::NextScene(Scene scene)
{
	// reassign std::unique_ptr make the old object destroyed and its memory deallocated :)
	currentScene = GetScene(scene);
	currentScene->LoadContent();
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
	}
}