#include "GameplayScene.h"
#include "SceneManager.h"

using namespace Castlevania;

GameplayScene::GameplayScene(SceneManager &sceneManager) : AbstractScene{ sceneManager }
{
	camera = std::make_unique<Camera>(sceneManager.GetGraphicsDevice());
	stageManager = std::make_unique<StageManager>();
}

void GameplayScene::LoadContent()
{
	auto &content = sceneManager.GetContent();

	stageManager->LoadContent(content);
	map = stageManager->NextMap(Map::STAGE_01_COURTYARD);
	camera->SetMoveArea(0, 0, map->GetWidthInPixels(), map->GetHeightInPixels());
	
	objectCollection = stageManager->LoadGameObjects();
	
	player = objectFactory.CreatePlayer();
	player->SetPosition(objectCollection.locations["Checkpoint"]);
	player->LoadContent(content);

	for (auto &entity : objectCollection.entities) // TODO: put LoadContent in constructor?
	{
		entity->LoadContent(content);
	}
}

void GameplayScene::Update(float deltaTime)
{
	camera->LookAt(player->GetOriginPosition(), Scrolling::Horizontally);

	player->Update(deltaTime, &objectCollection);

	for (auto const &gameObject : objectCollection.entities)
	{
		gameObject->Update(deltaTime);
	}
}

void GameplayScene::Draw(GameTime gameTime)
{
	auto &spriteBatch = sceneManager.GetSpriteBatch();

	spriteBatch.Begin(D3DXSPRITE_ALPHABLEND);

	map->Draw(spriteBatch);

	for (auto const &gameObject : objectCollection.entities)
	{
		gameObject->Draw(spriteBatch);
	}

	player->Draw(spriteBatch);

	spriteBatch.End();
}
