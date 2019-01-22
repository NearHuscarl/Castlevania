#include "Direct2DGame/Input/InputHelper.h"
#include "Direct2DGame/Utilities/CppExtensions.h"
#include "Stage.h"
#include "StageEvent.h"
#include "IntroCutscene.h"
#include "BossFightCutscene.h"
#include "HiddenMoneyBagCutscene.h"
#include "NextMapCutscene.h"
#include "NextRoomCutscene.h"
#include "LevelCompletedCutscene.h"
#include "GameOverCutscene.h"
#include "ResetCutscene.h"
#include "GoToCastleCutScene.h"
#include "CrossCutScene.h"
#include "StopwatchCutScene.h"
#include "../GameplayScene.h"
#include "../SceneManager.h"
#include "../../Models/UpdateData.h"
#include "../../Utilities/AudioManager.h"
#include "../../Utilities/TypeConverter.h"

using namespace Castlevania;

struct Stage::StageEvent
{
	StageEvent(int message, Subject &subject) : subject{ subject }
	{
		this->message = message;
	}

	int message;
	Subject &subject;
};

Stage::Stage(GameplayScene &gameplayScene, Map map, std::string spawnPoint) :
	gameplayScene{ gameplayScene },
	objectFactory{ gameplayScene.GetSceneManager().GetFactory() }
{
	this->currentMap = map;
	this->spawnPoint = spawnPoint;
	this->objectCollection = std::make_unique<ObjectCollection>();
}

void Stage::OnNotify(Subject &subject, int event)
{
	newEvent = std::make_unique<StageEvent>(event, subject);
}

Camera *Stage::GetCamera()
{
	return camera.get();
}

Hud *Stage::GetHud()
{
	return hud.get();
}

Rect Stage::GetActiveArea()
{
	return activeArea;
}

void Stage::LoadObjectsWithin(Rect area)
{
	auto &mapManager = gameplayScene.GetMapManager();
	auto &gridObjects = mapManager.GetMapObjectsInArea(currentMap, area);

	grid->PopulateObjects(gridObjects);

	auto mapObjectGroups = map->GetMapObjects();

	mapManager.GetForegrounds(objectCollection->foregroundObjects, mapObjectGroups, area);
	mapManager.GetAreas(objectCollection->staticObjects, mapObjectGroups, area);

	for (auto const &object : objectCollection->staticObjects)
	{
		if (object->GetId() == ObjectId::SpawnArea)
			object->Attach(grid.get());
	}

	camera->SetMoveArea(area);
}

void Stage::ClearObjectsWithin(Rect area, std::set<GameObject*> exceptionList)
{
	objectCollection->staticObjects.clear();
	objectCollection->foregroundObjects.clear();

	grid->GetCellsFromBoundingBox(activeArea, [&](CollisionCell &cell, int col, int row)
	{
		auto &entities = cell.GetObjects().entities;
		auto &staticObjects = cell.GetObjects().staticObjects;

		for (auto it = entities.end(); it != entities.begin(); )
		{
			std::advance(it, -1);
			auto entity = (*it).get();

			if (exceptionList.find(entity) == exceptionList.end())
				it = entities.erase(it);
		}

		for (auto it = staticObjects.end(); it != staticObjects.begin(); )
		{
			std::advance(it, -1);
			auto obj = (*it).get();
			auto objBbox = (Rect)obj->GetBoundingBox();

			if (obj->GetId() == ObjectId::Block)
				continue;

			if (exceptionList.find(obj) == exceptionList.end() && activeArea.Contains(objBbox))
				it = staticObjects.erase(it);
		}
	});
}

void Stage::Initialize()
{
	auto &graphicsDevice = gameplayScene.GetSceneManager().GetGraphicsDevice();
	auto &mapManager = gameplayScene.GetMapManager();

	player = gameplayScene.GetPlayer();
	player->AddObserver(*this);

	hud = gameplayScene.GetHud();
	data = gameplayScene.GetData();
	data->timeLeft.ResetLastSecond(); // When change to the next map, the last second is reset

	mapManager.SetWorldPosition(Vector2{ 0, (float)hud->GetHeight() });
	
	map = mapManager.GetTiledMap(currentMap);
	camera = std::make_unique<Camera>(graphicsDevice);

	auto cellWidth = (int)(camera->GetBounds().Width() / 2);
	auto cellHeight = (int)(camera->GetBounds().Height() / 2);
	
	grid = std::make_unique<CollisionGrid>(
		map->GetWidthInPixels() / cellWidth + 1,
		map->GetHeightInPixels() / cellHeight + 1,
		cellWidth,
		cellHeight);

	devTool = std::make_unique<DevTool>(*this);

	LoadMap();
}

void Stage::Update(GameTime gameTime)
{
	auto updateData = UpdateData{
		gameTime,
		camera->GetBounds(),
		player.get(),
		false,
		objectCollection.get(),
		nullptr,
	};

	switch (currentState)
	{
		case GameState::PLAYING:
			UpdateGameplay(updateData);
			break;

		default:
			currentCutscene->Update(updateData);
			break;
	}

	if (newEvent)
	{
		ProcessMessage(newEvent->message); // Make sure to handle new event after updating GameObjects
		newEvent = nullptr;
	}
}

void Stage::Draw(SpriteExtensions &spriteBatch)
{
	switch (currentState)
	{
		case GameState::PLAYING:
			DrawGameplay(spriteBatch);
			break;

		default:
			currentCutscene->Draw(spriteBatch);
			break;
	}
}

Rect Stage::GetCurrentArea(Vector2 position)
{
	auto &stageAreas = stageObject->stageAreas;

	if (stageAreas.empty())
	{
		return Rect{ 0, 0,
			map->GetWidthInPixels(),
			map->GetHeightInPixels() + hud->GetHeight() };
	}

	for (auto &area : stageAreas)
	{
		if (area->GetId() != ObjectId::StageArea)
			continue;

		auto viewportAreaBbox = area->GetBoundingBox();

		// Take account of hud height on top of the screen
		viewportAreaBbox.top -= hud->GetHeight();

		if (viewportAreaBbox.Contains(position))
		{
			return (Rect)viewportAreaBbox;
		}
	}

	return Rect::Empty();
}

void Stage::SetCurrentCutscene(GameState gameState)
{
	currentState = gameState;
	currentCutscene = ConstructCutscene(currentState);
}

void Stage::LoadMap()
{
	auto &content = gameplayScene.GetSceneManager().GetContent();
	auto &mapManager = gameplayScene.GetMapManager();
	
	devTool->LoadContent(content);

	stageObject = mapManager.GetStageObjects(currentMap);

	auto checkpoint = stageObject->locations[spawnPoint];

	player->SetPosition(checkpoint);
	player->Attach(grid.get());

	activeArea = GetCurrentArea(player->GetPosition());
	LoadObjectsWithin(activeArea);

	if (currentMap == Map::INTRO)
		SetCurrentCutscene(GameState::INTRO_CUTSCENE);
	else if (currentMap == Map::COURTYARD)
		AudioManager::PlaySong(M_BLOCK_01);
}

void Stage::Reset()
{
	auto &mapManager = gameplayScene.GetMapManager();

	ClearObjectsWithin(activeArea);
	LoadObjectsWithin(activeArea); // reload objects from the last active area

	for (auto [checkpointName, checkpoint] : stageObject->locations)
	{
		if (checkpointName != "Entrypoint" && !StartsWith(checkpointName, "Checkpoint"))
			continue;

		if (activeArea.Contains(checkpoint.position))
		{
			player->SetPosition(checkpoint);
			break;
		}
	}

	player->SetWhip(objectFactory.CreateWhip()); // reset whip to level 1
	player->Revive();
	data->timeLeft.SetCounter(STAGE_TIME);
	currentState = GameState::PLAYING;
}

void Stage::UpdateGameObjects(UpdateData &updateData)
{
	devTool->Update(updateData);

	auto cellCol = (int)(player->GetPosition().x / grid->GetCellWidth());
	auto cellRow = (int)(player->GetPosition().y / grid->GetCellHeight());
	auto collisionObjects = grid->GetCollisionObjects(cellCol, cellRow);

	updateData.collisionObjects = &collisionObjects;
	player->Update(updateData);

	if (data->timeLeft.GetCounter() < 0 || grid->IsOutOfRange(cellCol, cellRow))
		player->Die();

	for (auto const &object : objectCollection->staticObjects)
		object->Update(updateData);

	grid->Update(updateData);
}

void Stage::UpdateGameplay(UpdateData &updateData)
{
	// Dont follow if the player is dying because the dying sprite (player laying dead)
	// is wider than other sprites which make the camera glitching when getting
	// position from GetOriginPosition()
	if (player->GetState() == ObjectState::NORMAL)
		camera->LookAt(player->GetOriginPosition(), Scrolling::Horizontally);

	UpdateGameObjects(updateData);

	if (!updateData.isStopwatchActive)
	{
		auto &timeLeft = data->timeLeft;

		if (timeLeft.CountDown() &&
			timeLeft.GetCounter() >= 0 && timeLeft.GetCounter() < 30)
			AudioManager::Play(SE_TIMEOUT_WARNING);
	}
}

void Stage::DrawGameplay(SpriteExtensions &spriteBatch)
{
	map->Draw(spriteBatch);
	hud->Draw(spriteBatch);

	grid->GetCellsFromBoundingBox(camera->GetBounds(), [&](CollisionCell &cell, int col, int row)
	{
		auto &collisionObject = cell.GetObjects();

		for (auto const &staticObject : collisionObject.staticObjects)
			staticObject->Draw(spriteBatch);

		for (auto const &entity : collisionObject.entities)
			entity->Draw(spriteBatch);
	});

	player->Draw(spriteBatch);

	for (auto const &object : objectCollection->staticObjects)
		object->Draw(spriteBatch);

	for (auto const &fgObject : objectCollection->foregroundObjects)
		fgObject->Draw(spriteBatch);

	devTool->Draw(spriteBatch);
}

void Stage::OnNextMapCutsceneComplete()
{
	auto nextMapTrigger = player->GetNearbyObjects().nextMap;
	auto nextMap = nextMapTrigger->Property("Map");
	auto spawnPoint = nextMapTrigger->Property("SpawnPoint");
	//auto respawnPoint = RespawnPoint{};

	player->EnableControl(true); // quit player auto mode
	gameplayScene.NextStage(string2Map.at(nextMap), spawnPoint);
}

void Stage::OnNextRoomCutsceneComplete()
{
	activeArea = GetCurrentArea(player->GetPosition());
	LoadObjectsWithin(activeArea);

	gameplayScene.GetData()->stage++;
	currentState = GameState::PLAYING;
}

void Stage::ProcessMessage(int message)
{
	switch (message)
	{
		case NEXT_MAP_CUTSCENE_STARTED:
			SetCurrentCutscene(GameState::NEXT_MAP_CUTSCENE);
			break;

		case NEXT_MAP_CUTSCENE_ENDED:
			OnNextMapCutsceneComplete();
			break;

		case NEXT_ROOM_CUTSCENE_STARTED:
			SetCurrentCutscene(GameState::NEXT_ROOM_CUTSCENE);
			break;

		case NEXT_ROOM_CUTSCENE_ENDED:
			OnNextRoomCutsceneComplete();
			break;

		case BOSS_FIGHT_CUTSCENE_STARTED:
			SetCurrentCutscene(GameState::BOSS_FIGHT_CUTSCENE);
			break;

		case CUTSCENE_ENDED:
			currentState = GameState::PLAYING;
			break;

		case PLAYER_DIE:
			SetCurrentCutscene(GameState::RESET_STAGE_CUTSCENE);
			break;

		case BOSS_DIE:
			SetCurrentCutscene(GameState::LEVEL_COMPLETED_CUTSCENE);
			break;

		case GAME_OVER:
		case LEVEL_COMPLETED:
			SetCurrentCutscene(GameState::GAMEOVER_CUTSCENE);
			break;

		case RESET_STAGE_CUTSCENE_ENDED:
			Reset();
			break;

		case CROSS_POWERUP_ACTIVATED:
			SetCurrentCutscene(GameState::CROSS_CUTSCENE);
			break;

		case STOPWATCH_POWERUP_ACTIVATED:
			SetCurrentCutscene(GameState::STOPWATCH_CUTSCENE);
			break;

		case HIDDEN_MONEY_BAG_FOUND:
			SetCurrentCutscene(GameState::HIDDEN_MONEYBAG_CUTSCENE);
			break;

		case GO_TO_CASTLE_CUTSCENE_STARTED:
			SetCurrentCutscene(GameState::GO_TO_CASTLE_CUTSCENE);
			break;
	}
}

std::unique_ptr<Cutscene> Stage::ConstructCutscene(GameState gameState)
{
	auto &content = gameplayScene.GetSceneManager().GetContent();

	switch (gameState)
	{
		case GameState::INTRO_CUTSCENE:
			return std::make_unique<IntroCutscene>(*this, *grid, *player);

		case GameState::BOSS_FIGHT_CUTSCENE:
			return std::make_unique<BossFightCutscene>(*this, *grid, objectFactory);

		case GameState::NEXT_MAP_CUTSCENE:
			return std::make_unique<NextMapCutscene>(*this, content);

		case GameState::NEXT_ROOM_CUTSCENE:
			return std::make_unique<NextRoomCutscene>(*this, *stageObject, *grid, objectFactory, *player);

		case GameState::LEVEL_COMPLETED_CUTSCENE:
			return std::make_unique<LevelCompletedCutscene>(*this, *grid, objectFactory, *player, *data);
		
		case GameState::GAMEOVER_CUTSCENE:
			return std::make_unique<GameOverCutscene>(*this, content, gameplayScene);

		case GameState::RESET_STAGE_CUTSCENE:
			return std::make_unique<ResetCutscene>(*this, content);

		case GameState::CROSS_CUTSCENE:
			return std::make_unique<CrossCutscene>(*this, content, *grid);

		case GameState::STOPWATCH_CUTSCENE:
			return std::make_unique<StopwatchCutscene>(*this);

		case GameState::HIDDEN_MONEYBAG_CUTSCENE:
			return std::make_unique<HiddenMoneyBagCutscene>(*this, *stageObject, *grid, objectFactory);

		case GameState::GO_TO_CASTLE_CUTSCENE:
			return std::make_unique<GoToCastleCutscene>(*this, *objectCollection, *grid, *player);

		default:
			throw std::runtime_error("Cutscene not available");
	}
}

Stage::~Stage()
{
	if (player != nullptr)
		player->RemoveObserver(*this);
}
