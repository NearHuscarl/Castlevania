#include "Direct2DGame/Input/InputHelper.h"
#include "Stage.h"
#include "StageEvent.h"
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
	data = gameplayScene.GetData();
	data->timeLeft.ResetLastSecond(); // When change to the next map, the last second is reset

	mapManager.SetWorldPosition(Vector2{ 0, (float)hud->GetHeight() });
	camera = std::make_unique<Camera>(graphicsDevice);
	devTool = std::make_unique<DevTool>(gameplayScene, *camera);

	LoadMap();
}

void Stage::Update(GameTime gameTime)
{
	switch (currentState)
	{
		case GameState::PLAYING:
			UpdateGameplay(gameTime);
			break;

		default:
			currentCutscene->Update(gameTime);
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
	auto &viewportAreas = objectCollection.viewportAreas;

	if (viewportAreas.size() == 0)
	{
		return Rect{ 0, 0,
			map->GetWidthInPixels(),
			map->GetHeightInPixels() + hud->GetHeight() };
	}

	for (auto &viewportArea : viewportAreas)
	{
		auto viewportAreaBbox = viewportArea->GetBoundingBox();

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
	
	map = mapManager.GetTiledMap(currentMap);
	devTool->LoadContent(content);

	objectCollection = mapManager.GetOtherObjects(currentMap);
	objectCollection.player = player;
	objectCollection.player->SetPosition(objectCollection.locations[spawnPoint]);

	activeArea = GetCurrentArea(player->GetPosition());
	LoadObjectsWithin(activeArea);
}

void Stage::LoadObjectsWithin(Rect area)
{
	auto &mapManager = gameplayScene.GetMapManager();

	objectCollection.entities = mapManager.GetMapObjectsInArea(currentMap, area);
	camera->SetMoveArea(area);
}

void Stage::Reset()
{
	auto &mapManager = gameplayScene.GetMapManager();

	objectCollection = mapManager.GetOtherObjects(currentMap);
	objectCollection.player = player;
	LoadObjectsWithin(activeArea); // reload objects from the last active area

	for (auto [checkpoint, position] : objectCollection.locations)
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
	devTool->Update(gameTime, objectCollection);
	camera->LookAt(player->GetOriginPosition(), Scrolling::Horizontally);
	UpdateGameObjects(gameTime);
	data->timeLeft.CountDown();
}

void Stage::DrawGameplay(SpriteExtensions &spriteBatch)
{
	map->Draw(spriteBatch);
	hud->Draw(spriteBatch);

	for (auto const &entity : objectCollection.entities)
		entity->Draw(spriteBatch);

	for (auto const &boundaries : objectCollection.boundaries) // TODO: remove
		boundaries->Draw(spriteBatch);

	for (auto const &trigger : objectCollection.triggers)
		trigger->Draw(spriteBatch);

	player->Draw(spriteBatch);

	for (auto const &fgObject : objectCollection.foregroundObjects)
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

	objectCollection.boundaries.push_back(std::move(wall));
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

		case GO_TO_CASTLE_CUTSCENE_STARTED:
			SetCurrentCutscene(GameState::GO_TO_CASTLE_CUTSCENE);
			break;

		case PLAYER_DIE:
			SetCurrentCutscene(GameState::RESET_STAGE_CUTSCENE);
			break;

		case RESET_STAGE_CUTSCENE_ENDED:
			Reset();
			break;
	}
}

std::unique_ptr<Cutscene> Stage::ConstructCutscene(GameState gameState)
{
	auto &content = gameplayScene.GetSceneManager().GetContent();

	switch (gameState)
	{
		case GameState::NEXT_MAP_CUTSCENE:
			return std::make_unique<NextMapCutscene>(*this, content);

		case GameState::NEXT_ROOM_CUTSCENE:
			return std::make_unique<NextRoomCutscene>(*this, objectCollection);

		case GameState::RESET_STAGE_CUTSCENE:
			return std::make_unique<ResetCutscene>(*this, content);

		case GameState::GO_TO_CASTLE_CUTSCENE:
			return std::make_unique<GoToCastleCutscene>(*this, objectCollection);

		default:
			throw std::runtime_error("Cutscene not available");
	}
}

Stage::~Stage()
{
	if (player != nullptr)
		player->RemoveObserver(*this);
}
