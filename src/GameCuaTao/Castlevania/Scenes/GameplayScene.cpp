#include "Direct2DGame/Input/InputHelper.h"
#include "GameplayScene.h"
#include "SceneManager.h"
#include "SceneEvent.h"

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
	player->AddObserver(*this);
}

void GameplayScene::OnNotify(Subject &subject, int event)
{
	switch (event)
	{
		case GO_TO_CASTLE:
			currentState = GameState::GO_TO_CASTLE_TRANSITION;
			break;

		case NEXT_ROOM:
			currentState = GameState::NEXT_ROOM_TRANSITION;
			break;

		case TRANSITION_COMPLETED:
			currentState = GameState::PLAYING;
			break;
	}
}

void GameplayScene::LoadContent()
{
	auto &content = sceneManager.GetContent();

	mapManager->LoadContent(content);
	hud->LoadContent(content);
	hud->Register(player->GetData());

	LoadMap(Map::PLAYGROUND); // TODO: Change back to Map::COURTYARD
}

void GameplayScene::Update(GameTime gameTime)
{
	UpdateInput();

	switch (currentState)
	{
		case GameState::PLAYING:
			UpdateGameplay(gameTime);
			break;

		case GameState::GO_TO_CASTLE_TRANSITION:
			UpdateGoToCastleTransition();
			break;

		case GameState::NEXT_ROOM_TRANSITION:
			// - Viewport stays still
			// - Simon goes next to the door
			//	- Viewport moves to the middle
			//	- Door opens
			//	- Simon goes through door
			//	- Door closes
			//	- Viewport moves to the right
			// - stage++
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
		entity->Draw(spriteBatch);
		entity->DrawBoundingBox(spriteBatch); // NOTE: remove
	}

	for (auto const &trigger : objectCollection.triggers)
	{
		trigger->Draw(spriteBatch);
	}

	player->Draw(spriteBatch);
	player->DrawBoundingBox(spriteBatch); // NOTE: remove

	spriteBatch.End();
}

UpdateData GameplayScene::GetUpdateData()
{
	return UpdateData{
		sceneManager.GetGraphicsDevice().GetViewport(),
		&objectCollection,
	};
}

void GameplayScene::LoadMap(Map mapName)
{
	map = mapManager->NextMap(mapName);

	camera->SetMoveArea(0, 0,
		map->GetWidthInPixels(),
		map->GetHeightInPixels() + hud->GetHeight());

	objectCollection = mapManager->LoadGameObjects();

	player->SetPosition(objectCollection.locations["Checkpoint"]);
}

void GameplayScene::UpdateInput()
{
	if (mapManager->GetCurrentMap() == Map::PLAYGROUND)
	{
		auto locations = objectCollection.locations;

		if (InputHelper::IsKeyDown(DIK_HOME))
			LoadMap(Map::COURTYARD);
		else if (InputHelper::IsKeyDown(DIK_1))
			player->SetPosition(locations["Checkpoint"]);
		else if (InputHelper::IsKeyDown(DIK_2))
			player->SetPosition(locations["Checkpoint_02"]);
		else if (InputHelper::IsKeyDown(DIK_3))
			player->SetPosition(locations["Checkpoint_03"]);
		else if (InputHelper::IsKeyDown(DIK_4))
			player->SetPosition(locations["Checkpoint_04"]);
		else if (InputHelper::IsKeyDown(DIK_5))
			player->SetPosition(locations["Checkpoint_05"]);
		else if (InputHelper::IsKeyDown(DIK_6))
			player->SetPosition(locations["Checkpoint_06"]);
		else if (InputHelper::IsKeyDown(DIK_NUMPAD1))
		{
			auto object = objectFactory.CreateZombie(locations["Checkpoint_05"]);
			object->WalkRight();
			objectCollection.entities.push_back(std::move(object));
		}
		else if (InputHelper::IsKeyDown(DIK_W))
		{
			auto playerLocation = player->GetPosition();
			auto spawnLocation = Vector2{ playerLocation.x + 60, playerLocation.y - 100 };
			objectCollection.entities.push_back(objectFactory.CreateWhipPowerup(spawnLocation));
		}

		auto &viewport = sceneManager.GetGraphicsDevice().GetViewport();

		if (!camera->GetBounds().Intersects(player->GetFrameRect())) // player outside of viewport, update viewport postiion
		{
			camera->LookAt(player->GetPosition());
		}
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

	player->Update(gameTime, GetUpdateData());

	auto &entities = objectCollection.entities;

	// Only update existing objects. Any new objects will have to wait until next turn
	// That's way, a newly spawned object wont get a chance to act during the same frame
	// that it was spawned, before the player has even had a chance to see it
	auto sizeThisTurn = entities.size();

	for (unsigned int i = 0; i < sizeThisTurn; i++)
	{
		entities[i]->Update(gameTime, GetUpdateData());
	}

	objectCollection.RemoveDeadObjects();
}

void GameplayScene::UpdateGoToCastleTransition()
{
	//auto originalSpeed = player->Get
	//player->SetSpeed();
}

GameplayScene::~GameplayScene()
{
	player->RemoveObserver(*this);
}
