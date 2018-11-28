#include "Direct2DGame/Input/InputHelper.h"
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
	
	mapManager = std::make_unique<MapManager>(objectFactory);
	mapManager->SetWorldPosition(Vector2{ 0, (float)hud->GetHeight() });

	player = objectFactory.CreatePlayer();
}

void GameplayScene::LoadContent()
{
	auto &content = sceneManager.GetContent();

	mapManager->LoadContent(content);
	hud->LoadContent(content);
	hud->Register(player->GetData());

	LoadMap(Map::COURTYARD);
}

void GameplayScene::Update(GameTime gameTime)
{
	UpdateInput();

	switch (gameState)
	{
		case GameState::PLAYING:
			UpdateGameplay(gameTime);
			break;

		case GameState::NEXT_ROOM_TRANSITION:
			// - Simon go to door
			//	- Viewport move to middle
			//	- Door open
			//	- Simon go through door
			//	- Door close
			//	- Viewport move to right
			//player->GetData().stage++;
			break;
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

	for (auto const &trigger : objectCollection.triggers)
	{
		trigger->Draw(spriteBatch);
	}

	player->DrawBoundingBox(spriteBatch); // NOTE: remove
	player->Draw(spriteBatch);

	spriteBatch.End();
}

void GameplayScene::LoadMap(Map mapName)
{
	map = mapManager->NextMap(mapName);
	camera->SetMoveArea(0, 0, map->GetWidthInPixels(), map->GetHeightInPixels());

	objectCollection = mapManager->LoadGameObjects();

	player->SetPosition(objectCollection.locations["Checkpoint"]);

	updateData = UpdateData{
		sceneManager.GetGraphicsDevice().GetViewport(),
		&objectCollection,
	};
}

void GameplayScene::UpdateInput()
{
	if (mapManager->GetCurrentMap() == Map::PLAYGROUND)
	{
		if (InputHelper::IsKeyDown(DIK_HOME))
			LoadMap(Map::COURTYARD);
		else if (InputHelper::IsKeyDown(DIK_1))
			player->SetPosition(objectCollection.locations["Checkpoint"]);
		else if (InputHelper::IsKeyDown(DIK_2))
			player->SetPosition(objectCollection.locations["Checkpoint_02"]);
		else if (InputHelper::IsKeyDown(DIK_3))
			player->SetPosition(objectCollection.locations["Checkpoint_03"]);
		else if (InputHelper::IsKeyDown(DIK_4))
			player->SetPosition(objectCollection.locations["Checkpoint_04"]);
		else if (InputHelper::IsKeyDown(DIK_W))
			objectCollection.entities.push_back(objectFactory.CreateWhipPowerup(Vector2{ 110, 150 }));
	}
	else
	{
		if (InputHelper::IsKeyDown(DIK_HOME))
			LoadMap(Map::PLAYGROUND);
	}
}

void GameplayScene::UpdateGameplay(GameTime gameTime)
{
	camera->LookAt(player->GetOriginPosition(), Scrolling::Horizontally);

	player->Update(gameTime, updateData);

	auto &entities = objectCollection.entities;

	// Only update existing objects. Any new objects will have to wait until next turn
	// That's way, a newly spawned object wont get a chance to act during the same frame
	// that it was spawned, before the player has even had a chance to see it
	auto sizeThisTurn = entities.size();

	for (unsigned int i = 0; i < sizeThisTurn; i++)
	{
		entities[i]->Update(gameTime, updateData);
	}

	objectCollection.RemoveDeadObjects();
}
