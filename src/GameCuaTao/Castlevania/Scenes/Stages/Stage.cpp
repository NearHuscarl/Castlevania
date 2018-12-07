#include "Direct2DGame/Input/InputHelper.h"
#include "Stage.h"
#include "StageEvent.h"
#include "../GameplayScene.h"
#include "../SceneManager.h"
#include "../../Models/UpdateData.h"
#include "../../Utilities/TypeConverter.h"

using namespace Castlevania;

constexpr auto NEXT_MAP_TRANSITION_TIME = 400; // in milliseconds

Stage::Stage(GameplayScene &gameplayScene, Map map) :
	gameplayScene{ gameplayScene },
	objectFactory{ gameplayScene.GetSceneManager().GetFactory() }
{
	currentMap = map;
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
	devTool = std::make_unique<DevTool>(objectFactory, *camera);

	LoadMap(currentMap);
}

void Stage::Update(GameTime gameTime)
{
}

void Stage::Draw(SpriteExtensions &spriteBatch)
{
	switch (currentState)
	{
		case GameState::PLAYING:
			DrawGameplay(spriteBatch);
			break;

		case GameState::NEXT_MAP_CUTSCENE:
			DrawNextMapCutscene(spriteBatch);
			break;

		// In the original game, when change to cutscene, all in-game objects
		// except tiled map, simon and the door are invisible on the screen
		default: // Handle other cutscenes
			DrawCutscene(spriteBatch);
			break;
	}
}

void Stage::LoadMap(Map mapName)
{
	auto &content = gameplayScene.GetSceneManager().GetContent();
	auto &mapManager = gameplayScene.GetMapManager();
	auto &mapData = mapManager.LoadMap(mapName);
	
	map = mapData.map;
	objectCollection = std::move(mapData.objects);
	objectCollection.player = player;

	camera->SetMoveArea(0, 0,
		map->GetWidthInPixels(),
		map->GetHeightInPixels() + hud->GetHeight());

	devTool->LoadContent(content);

	player->SetPosition(objectCollection.locations["Checkpoint"]);

	for (auto &trigger : objectCollection.triggers)
	{
		if (trigger->GetTriggerType() == TriggerType::NEXT_MAP)
		{
			nextMapTrigger = trigger.get();
			break;
		}
	}
}

void Stage::UpdateInput()
{
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
	devTool->Update(objectCollection);
	UpdateGameObjects(gameTime);
	camera->LookAt(player->GetOriginPosition(), Scrolling::Horizontally);
	data->timeLeft.CountDown();
}

void Stage::DrawGameplay(SpriteExtensions &spriteBatch)
{
	map->Draw(spriteBatch);
	hud->Draw(spriteBatch);

	for (auto const &entity : objectCollection.entities)
	{
		entity->Draw(spriteBatch);
	}

	for (auto const &boundaries : objectCollection.boundaries) // TODO: remove
	{
		boundaries->Draw(spriteBatch);
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

	devTool->Draw(spriteBatch);
}

void Stage::DrawNextMapCutscene(SpriteExtensions &spriteBatch)
{
	spriteBatch.Draw(gameplayScene.GetCutsceneBackground(), Vector2::Zero());
}

void Stage::DrawCutscene(SpriteExtensions &spriteBatch)
{
	map->Draw(spriteBatch);
	hud->Draw(spriteBatch);

	player->Draw(spriteBatch);

	for (auto const &fgObject : objectCollection.foregroundObjects)
	{
		fgObject->Draw(spriteBatch);
	}
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
		auto nextMap = nextMapTrigger->Property("Map");

		player->EnableControl(true); // quit player auto mode
		gameplayScene.NextStage(string2Map.at(nextMap));
		OnNotify(Subject::Empty(), NEXT_MAP_CUTSCENE_ENDED);
	}
}

Stage::~Stage()
{
	if (player != nullptr)
		player->RemoveObserver(*this);
}
