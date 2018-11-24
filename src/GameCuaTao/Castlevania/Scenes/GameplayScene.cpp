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

	for (auto const &entity : objectCollection.entities)
	{
		entity->DrawBoundingBox(spriteBatch); // NOTE: remove
		entity->Draw(spriteBatch);
	}

	player->DrawBoundingBox(spriteBatch); // NOTE: remove
	player->Draw(spriteBatch);

	spriteBatch.End();
}
