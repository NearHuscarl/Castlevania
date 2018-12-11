#include "GreatHallStage.h"
#include "StageEvent.h"

using namespace Castlevania;

constexpr auto CAMERA_CUTSCENE_SPEED = 140.0f;
auto destinationPosition_x = 0.0f;
auto openDoorPosition_x = 0.0f;

GreatHallStage::GreatHallStage(GameplayScene &gameplayScene) : Stage{ gameplayScene, Map::GREAT_HALL }
{
}

void GreatHallStage::OnNotify(Subject &subject, int event)
{
	switch (event)
	{
		case NEXT_ROOM_CUTSCENE_STARTED:
			SetupNextRoomCutscene();
			break;

		case NEXT_ROOM_CUTSCENE_ENDED:
			door = nullptr;
			break;

		case CUTSCENE_ENDED:
			currentState = GameState::PLAYING;
			break;
	}
}

void GreatHallStage::Update(GameTime gameTime)
{
	switch (currentState)
	{
		case GameState::PLAYING:
			UpdateGameplay(gameTime);
			break;

		// Viewport stays still
		// Simon goes next to the door
		//	Viewport moves to the middle
		//	Door opens
		//	Simon goes through door
		//	Door closes
		//	Viewport moves to the right
		// stage++
		case GameState::NEXT_ROOM_CUTSCENE:
			UpdateNextRoomCutscene(gameTime);
			break;
	}
}

void GreatHallStage::SetupNextRoomCutscene()
{
	auto cameraRect = camera->GetBounds();

	door = player->GetNearbyObjects().door;
	destinationPosition_x = cameraRect.left + cameraRect.Width();
	openDoorPosition_x = cameraRect.left + cameraRect.Width() / 2;

	camera->SetMoveArea(Rect::Empty()); // camera can move freely in cutscene
	player->EnableControl(false);
	currentState = GameState::NEXT_ROOM_CUTSCENE;
}

void GreatHallStage::UpdateNextRoomCutscene(GameTime gameTime)
{
	UpdateGameObjects(gameTime);

	auto deltaTime = (float)gameTime.ElapsedGameTime.Seconds();
	auto cameraDistance = CAMERA_CUTSCENE_SPEED * deltaTime;

	camera->Move(Vector2{ cameraDistance, 0 });

	if (camera->GetBounds().X() >= openDoorPosition_x)
	{
		door->Open();
	}
}
