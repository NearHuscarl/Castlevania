#include "GameplayScene.h"
#include "SceneManager.h"

using namespace Castlevania;

GameplayScene::GameplayScene(SceneManager &sceneManager, ObjectFactory &objectFactory) :
	AbstractScene{ sceneManager },
	objectFactory{ objectFactory }
{
	auto &graphicsDevice = sceneManager.GetGraphicsDevice();

	camera = std::make_unique<Camera>(graphicsDevice);
	hud = std::make_unique<Hud>(graphicsDevice);
	
	stageManager = std::make_unique<StageManager>(objectFactory);
	stageManager->SetWorldPosition(Vector2{ 0, (float)hud->GetHeight() });

	player = objectFactory.CreatePlayer();
}

void GameplayScene::LoadContent()
{
	auto &content = sceneManager.GetContent();

	stageManager->LoadContent(content);
	hud->LoadContent(content);
	hud->Register(player->GetData());

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

	// Only update existing objects. Any new objects will have to wait until next turn
	// That's way, a newly spawned object wont get a chance to act during the same frame
	// that it was spawned, before the player has even had a chance to see it
	auto sizeThisTurn = entities.size();

	for (unsigned int i = 0; i < sizeThisTurn; i++)
	{
		entities[i]->Update(deltaTime, &objectCollection);
	}

	objectCollection.RemoveDeadObjects();
}

void GameplayScene::Draw(GameTime gameTime)
{
	auto &spriteBatch = sceneManager.GetSpriteBatch();

	spriteBatch.Begin(D3DXSPRITE_ALPHABLEND);

	map->Draw(spriteBatch);
	hud->Draw(spriteBatch);

	for (auto const &entity : objectCollection.entities)
	{
		entity->DrawBoundingBox(spriteBatch); // NOTE: remove
		entity->Draw(spriteBatch);
	}

	player->DrawBoundingBox(spriteBatch); // NOTE: remove
	player->Draw(spriteBatch);

	spriteBatch.End();
}
