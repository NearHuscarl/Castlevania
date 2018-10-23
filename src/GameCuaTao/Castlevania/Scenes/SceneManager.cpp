#include "SceneManager.h"
#include "MenuScene.h"
#include "IntroScene.h"
#include "GameplayScene.h"

using namespace Castlevania;

SceneManager::SceneManager(std::shared_ptr<ContentManager> content)
{
	this->content = content;
}

void SceneManager::Update(float deltaTime)
{
	currentScene->Update(deltaTime);
}

void SceneManager::Draw(SpriteBatch &spriteBatch)
{
	currentScene->Draw(spriteBatch);
}

void SceneManager::NextScene(Scene scene)
{
	// reassign std::unique_ptr make the old object destroyed and its memory deallocated :)
	currentScene = GetScene(scene);
	currentScene->LoadContent(*content);
}

AbstractScene *SceneManager::GetCurrentScene()
{
	return currentScene.get();
}


std::unique_ptr<AbstractScene> Castlevania::SceneManager::GetScene(Scene scene)
{
	switch (scene)
	{
		case Scene::MENU:
			return std::make_unique<MenuScene>();
		
		case Scene::INTRO:
			return std::make_unique<IntroScene>();
		
		case Scene::GAMEPLAY:
			return std::make_unique<GameplayScene>();
	}
}