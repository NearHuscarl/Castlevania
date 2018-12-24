#include "Direct2DGame/Input/InputHelper.h"
#include "Stage.h"
#include "StageEvent.h"
#include "BossFightCutscene.h"
#include "NextMapCutscene.h"
#include "NextRoomCutscene.h"
#include "ResetCutscene.h"
#include "GoToCastleCutScene.h"
#include "../GameplayScene.h"
#include "../SceneManager.h"
#include "../../Models/UpdateData.h"
#include "../../Utilities/CppExtensions.h"
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
		stageObject.get(),
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

	if (stageAreas.size() == 0)
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

	auto checkpoint = stageObject->checkpoints[spawnPoint];

	player->SetPosition(checkpoint);
	player->Attach(grid.get());

	activeArea = GetCurrentArea(player->GetPosition());
	LoadObjectsWithin(activeArea);

	for (auto const &spawnArea : stageObject->spawnAreas)
		spawnArea->Attach(grid.get());
}

void Stage::LoadObjectsWithin(Rect area)
{
	auto &mapManager = gameplayScene.GetMapManager();
	auto &objectCollection = mapManager.GetMapObjectsInArea(currentMap, area);
	
	grid->PopulateObjects(objectCollection);

	for (auto const &spawnArea : stageObject->spawnAreas)
	{
		if (area.Contains((Rect)spawnArea->GetBoundingBox()))
			spawnArea->GetBody().Enabled(true);
		else
			spawnArea->GetBody().Enabled(false);
	}

	camera->SetMoveArea(area);
}

void Stage::Reset()
{
	auto &mapManager = gameplayScene.GetMapManager();

	LoadObjectsWithin(activeArea); // reload objects from the last active area

	for (auto [checkpoint, position] : stageObject->checkpoints)
	{
		if (checkpoint != "Entrypoint" && !StartsWith(checkpoint, "Checkpoint"))
			continue;

		if (activeArea.Contains(position))
		{
			player->SetPosition(position);
			break;
		}
	}

	player->Revive();
	currentState = GameState::PLAYING;
}

void Stage::UpdateGameObjects(UpdateData &updateData)
{
	grid->Update(updateData);
}

void Stage::UpdateGameplay(UpdateData &updateData)
{
	devTool->Update(updateData);
	camera->LookAt(player->GetOriginPosition(), Scrolling::Horizontally);
	UpdateGameObjects(updateData);
	data->timeLeft.CountDown();
}

void Stage::DrawGameplay(SpriteExtensions &spriteBatch)
{
	map->Draw(spriteBatch);
	hud->Draw(spriteBatch);

	auto existedBlocks = std::vector<GameObject*>{};

	// TODO: divide big block into smaller blocks so grid can consume it
	grid->GetCellsFromBoundingBox(camera->GetBounds(), [&](CollisionCell &cell, int col, int row)
	{
		auto &collisionObject = cell.GetObjects();

		for (auto &block : collisionObject.blocks)
		{
			auto existed = false;

			for (auto existedBlock : existedBlocks)
			{
				if (block.get() == existedBlock)
				{
					existed = true;
					break;
				}
			}

			if (!existed)
			{
				existedBlocks.push_back(block.get());
				block->Draw(spriteBatch);
			}
		}

		for (auto const &staticObject : collisionObject.staticObjects)
			staticObject->Draw(spriteBatch);

		for (auto const &entity : collisionObject.entities)
			entity->Draw(spriteBatch);
	});

	player->Draw(spriteBatch);

	for (auto const &spawnArea : stageObject->spawnAreas)
		spawnArea->Draw(spriteBatch);

	for (auto const &fgObject : stageObject->foregroundObjects)
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
	auto &door = dynamic_cast<NextRoomCutscene&>(*currentCutscene).GetDoor();
	auto wall = objectFactory.CreateBoundary(door.GetBoundingBox());

	grid->Add(std::move(wall), CollisionObjectType::Static);
	door.Destroy();

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

		case BOSS_FIGHT_STARTED:
			currentState = GameState::PLAYING;
			break;

		case PLAYER_DIE:
			SetCurrentCutscene(GameState::RESET_STAGE_CUTSCENE);
			break;

		case RESET_STAGE_CUTSCENE_ENDED:
			Reset();
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
		case GameState::BOSS_FIGHT_CUTSCENE:
			return std::make_unique<BossFightCutscene>(*this, *grid, objectFactory);

		case GameState::NEXT_MAP_CUTSCENE:
			return std::make_unique<NextMapCutscene>(*this, content);

		case GameState::NEXT_ROOM_CUTSCENE:
			return std::make_unique<NextRoomCutscene>(*this, *stageObject, *grid, *player);

		case GameState::RESET_STAGE_CUTSCENE:
			return std::make_unique<ResetCutscene>(*this, content);

		case GameState::GO_TO_CASTLE_CUTSCENE:
			return std::make_unique<GoToCastleCutscene>(*this, *stageObject, *grid, *player);

		default:
			throw std::runtime_error("Cutscene not available");
	}
}

Stage::~Stage()
{
	if (player != nullptr)
		player->RemoveObserver(*this);
}
