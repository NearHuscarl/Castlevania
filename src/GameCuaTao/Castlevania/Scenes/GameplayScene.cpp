#include "GameplayScene.h"
#include "SceneManager.h"

using namespace Castlevania;

GameplayScene::GameplayScene(SceneManager &sceneManager, ObjectFactory &objectFactory) :
	AbstractScene{ sceneManager },
	objectFactory{ objectFactory }
{
	camera = std::make_unique<Camera>(sceneManager.GetGraphicsDevice());
	stageManager = std::make_unique<StageManager>(objectFactory);

	player = objectFactory.CreatePlayer();
	hud = std::make_unique<Hud>(player->GetData());
}

void GameplayScene::LoadContent()
{
	auto &content = sceneManager.GetContent();

	stageManager->LoadContent(content);
	hud->LoadContent(content);

	map = stageManager->NextMap(Map::STAGE_01_COURTYARD);
	camera->SetMoveArea(0, 0, map->GetWidthInPixels(), map->GetHeightInPixels());
	
	objectCollection = stageManager->LoadGameObjects();
	
	player->SetPosition(objectCollection.locations["Checkpoint"]);
}

void GameplayScene::Update(float deltaTime)
{
	camera->LookAt(player->GetOriginPosition(), Scrolling::Horizontally);

	player->Update(deltaTime, &objectCollection);
	auto &entities = objectCollection.entities;

	for (auto const &entity : entities)
	{
		entity->Update(deltaTime, &objectCollection);
	}

	for (int i = entities.size() - 1; i >= 0; i--) // Remove dead objects
	{
		auto &entity = entities[i];

		if (entity->IsDestroyed())
			entities.erase(entities.begin() + i);
	}
}

void GameplayScene::Draw(GameTime gameTime)
{
	auto &spriteBatch = sceneManager.GetSpriteBatch();

	spriteBatch.Begin(D3DXSPRITE_ALPHABLEND);

	map->Draw(spriteBatch);
	hud->Draw(spriteBatch);
	auto &entities = objectCollection.entities;

	for (auto const &entity : entities)
	{
		entity->DrawBoundingBox(spriteBatch); // NOTE: remove
		entity->Draw(spriteBatch);
	}

	player->DrawBoundingBox(spriteBatch); // NOTE: remove
	player->Draw(spriteBatch);

	spriteBatch.End();
}
