#include "Direct2DGame/Input/InputHelper.h"
#include "Stage.h"
#include "StageEvent.h"
#include "../GameplayScene.h"
#include "../SceneManager.h"
#include "../../Models/UpdateData.h"
#include "../../Utilities/TypeConverter.h"

using namespace Castlevania;

constexpr auto NEXT_MAP_TRANSITION_TIME = 400; // in milliseconds

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
	if (newEvent)
	{
		ProcessMessage(); // Make sure to handle new event after updating GameObjects
		newEvent = nullptr;
	}
}

void Stage::Draw(SpriteExtensions &spriteBatch)
{
	switch (currentState)
	{
		case GameState::NEXT_MAP_CUTSCENE:
			DrawNextMapCutscene(spriteBatch);
			break;

		default:
			DrawGameplay(spriteBatch);
			break;
	}
}

void Stage::LoadMap()
{
	auto &content = gameplayScene.GetSceneManager().GetContent();
	auto &mapManager = gameplayScene.GetMapManager();
	
	map = mapManager.GetTiledMap(currentMap);

	devTool->LoadContent(content);

	// Load game objects
	objectCollection = mapManager.GetOtherObjects(currentMap);
	objectCollection.player = player;
	objectCollection.player->SetPosition(objectCollection.locations[spawnPoint]);

	LoadObjectsInCurrentArea();
}

void Stage::LoadObjectsInCurrentArea()
{
	auto &mapManager = gameplayScene.GetMapManager();
	auto &viewportAreas = objectCollection.viewportAreas;

	if (viewportAreas.size() == 0)
	{
		objectCollection.entities = mapManager.GetMapObjects(currentMap);

		camera->SetMoveArea(0, 0,
			map->GetWidthInPixels(),
			map->GetHeightInPixels() + hud->GetHeight());

		return;
	}

	for (auto &viewportArea : viewportAreas)
	{
		auto viewportAreaBbox = viewportArea->GetBoundingBox();

		// Take account of hud height on top of the screen
		viewportAreaBbox.top -= hud->GetHeight();

		// Only load object in the active area (room)
		if (viewportAreaBbox.TouchesOrIntersects(player->GetBoundingBox()))
		{
			objectCollection.entities = mapManager.GetMapObjectsInArea(currentMap, (Rect)viewportAreaBbox);
			camera->SetMoveArea((Rect)viewportAreaBbox);
			break;
		}
	}
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
	devTool->Update(objectCollection);
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

void Stage::DrawNextMapCutscene(SpriteExtensions &spriteBatch)
{
	spriteBatch.Draw(gameplayScene.GetCutsceneBackground(), Vector2::Zero());
}

void Stage::SetupNextMapCutscene()
{
	nextMapTimer.Start();
	currentState = GameState::NEXT_MAP_CUTSCENE;
}

void Stage::UpdateNextMapCutscene(GameTime gameTime)
{
	if (nextMapTimer.ElapsedMilliseconds() >= NEXT_MAP_TRANSITION_TIME)
	{
		auto nextMapTrigger = player->GetNearbyObjects().nextMap;
		auto nextMap = nextMapTrigger->Property("Map");
		auto spawnPoint = nextMapTrigger->Property("SpawnPoint");

		player->EnableControl(true); // quit player auto mode
		gameplayScene.NextStage(string2Map.at(nextMap), spawnPoint);

		OnNotify(Subject::Empty(), NEXT_MAP_CUTSCENE_ENDED);
	}

	ProcessMessage();
}

Stage::~Stage()
{
	if (player != nullptr)
		player->RemoveObserver(*this);
}
