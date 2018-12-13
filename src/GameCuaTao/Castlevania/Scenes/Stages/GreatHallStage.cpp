#include "GreatHallStage.h"
#include "StageEvent.h"
#include "../GameplayScene.h"

using namespace Castlevania;

GreatHallStage::GreatHallStage(GameplayScene &gameplayScene, std::string spawnPoint) :
	Stage{ gameplayScene, Map::GREAT_HALL, spawnPoint }
{
}

void GreatHallStage::Update(GameTime gameTime)
{
	switch (currentState)
	{
		case GameState::PLAYING:
			UpdateGameplay(gameTime);
			break;

		case GameState::NEXT_MAP_CUTSCENE:
			UpdateNextMapCutscene(gameTime);
			break;

		case GameState::NEXT_ROOM_CUTSCENE:
			UpdateNextRoomCutscene(gameTime);
			break;
	}

	Stage::Update(gameTime);
}

void GreatHallStage::SetupNextRoomCutscene()
{
	camera->SetMoveArea(Rect::Empty()); // camera can move freely in cutscene

	auto door = player->GetNearbyObjects().door;

	// Clear all objects in current room because they will not be needed
	// anymore once player go to the next room. The door is the only exception
	// here since it is part of the next room cutscene. It will be deleted later
	// after the cutscene is finished
	auto &entities = objectCollection.entities;

	for (int i = entities.size() - 1; i >= 0; i--)
	{
		auto &entity = entities[i];

		if (entity.get() != door)
			entities.erase(entities.begin() + i);
	}

	nextRoomCutscene = std::make_unique<NextRoomCutscene>(*player, *camera, *door);
	currentState = GameState::NEXT_ROOM_CUTSCENE;
}

void GreatHallStage::UpdateNextRoomCutscene(GameTime gameTime)
{
	UpdateGameObjects(gameTime);
	nextRoomCutscene->Update(gameTime);

	if (nextRoomCutscene->IsComplete())
		OnNotify(Subject::Empty(), NEXT_ROOM_CUTSCENE_ENDED);
}

void GreatHallStage::OnNextRoomCutsceneComplete()
{
	auto &door = nextRoomCutscene->GetDoor();
	auto wall = objectFactory.CreateBoundary(door.GetBoundingBox());

	objectCollection.boundaries.push_back(std::move(wall));
	door.Destroy();

	LoadObjectsInCurrentArea();
	gameplayScene.GetData()->stage++;
	currentState = GameState::PLAYING;
}

void GreatHallStage::ProcessMessage()
{
	if (newEvent == nullptr)
		return;

	switch (newEvent->message)
	{
		case NEXT_MAP_CUTSCENE_STARTED:
			SetupNextMapCutscene();
			break;

		case NEXT_ROOM_CUTSCENE_STARTED:
			SetupNextRoomCutscene();
			break;

		case NEXT_ROOM_CUTSCENE_ENDED:
			OnNextRoomCutsceneComplete();
			break;
	}
}
