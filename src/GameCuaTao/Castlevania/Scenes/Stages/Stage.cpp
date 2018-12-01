#include "Direct2DGame/Input/InputHelper.h"
#include "Stage.h"
#include "../GameplayScene.h"
#include "../SceneManager.h"

using namespace Castlevania;

Stage::Stage(GameplayScene &gameplayScene, Map map) :
	gameplayScene{ gameplayScene },
	objectFactory{ gameplayScene.GetSceneManager().GetFactory() }
{
	mapName = map;
}

UpdateData Stage::GetUpdateData()
{
	return UpdateData{
		camera->GetBounds(),
		&objectCollection,
	};
}

void Stage::Initialize()
{
	auto &graphicsDevice = gameplayScene.GetSceneManager().GetGraphicsDevice();
	auto &mapManager = gameplayScene.GetMapManager();

	player = gameplayScene.GetPlayer();
	player->AddObserver(*this);

	hud = gameplayScene.GetHud();

	mapManager.SetWorldPosition(Vector2{ 0, (float)hud->GetHeight() });
	camera = std::make_unique<Camera>(graphicsDevice);

	LoadMap(mapName);
}

void Stage::Update(GameTime gameTime)
{
}

void Stage::Draw(SpriteExtensions &spriteBatch)
{
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

	for (auto const &fgObject : objectCollection.foregroundObjects)
	{
		fgObject->Draw(spriteBatch);
	}

	player->DrawBoundingBox(spriteBatch); // NOTE: remove

	spriteBatch.End();
}

void Stage::LoadMap(Map mapName)
{
	auto &mapManager = gameplayScene.GetMapManager();
	auto &mapData = mapManager.LoadMap(mapName);
	
	map = mapData.map;
	objectCollection = std::move(mapData.objects);

	camera->SetMoveArea(0, 0,
		map->GetWidthInPixels(),
		map->GetHeightInPixels() + hud->GetHeight());

	player->SetPosition(objectCollection.locations["Checkpoint"]);
}

void Stage::UpdateInput()
{
	auto &mapManager = gameplayScene.GetMapManager();

	if (InputHelper::IsKeyDown(DIK_HOME))
		gameplayScene.NextStage(Map::PLAYGROUND);
}

void Stage::UpdateGameObjects(GameTime gameTime)
{
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

void Stage::UpdateGameplay(GameTime gameTime)
{
	camera->LookAt(player->GetOriginPosition(), Scrolling::Horizontally);
	UpdateGameObjects(gameTime);
}

Stage::~Stage()
{
	if (player != nullptr)
		player->RemoveObserver(*this);
}
