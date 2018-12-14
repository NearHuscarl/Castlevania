#include "Direct2DGame/Extensions/Animations/AnimatedSprite.h"
#include "NextRoomCutscene.h"
#include "Stage.h"
#include "StageEvent.h"

using namespace Castlevania;

constexpr auto CAMERA_CUTSCENE_SPEED = 140.0f;
constexpr auto WALK_DISTANCE = 135;

enum class NextRoomCutscene::State
{
	VIEWPORT_MOVING_FIRST_HALF,
	OPENING_DOOR,
	GOING_TO_NEXT_ROOM,
	CLOSING_DOOR,
	VIEWPORT_MOVING_SECOND_HALF,
};

NextRoomCutscene::NextRoomCutscene(Stage &stage, ObjectCollection &objectCollection) : Cutscene{ stage }
{
	camera = stage.GetCamera();
	camera->SetMoveArea(Rect::Empty()); // camera can move freely in cutscene

	player = objectCollection.player.get();
	door = player->GetNearbyObjects().door;

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

	SetupCutscene();
}

void NextRoomCutscene::SetupCutscene()
{
	player->EnableControl(false);
	doorHitDirection = player->GetNearbyObjects().doorHitDirection;

	auto cameraRect = camera->GetBounds();

	viewportDestination_x = cameraRect.left + cameraRect.Width();
	openDoorPosition_x = cameraRect.left + cameraRect.Width() / 2;

	currentState = State::VIEWPORT_MOVING_FIRST_HALF;
}

Door &NextRoomCutscene::GetDoor()
{
	return *door;
}

void NextRoomCutscene::Update(GameTime gameTime)
{
	if (isComplete)
		return;

	stage.UpdateGameObjects(gameTime);

	switch (currentState)
	{
		case State::VIEWPORT_MOVING_FIRST_HALF:
		{
			auto deltaTime = (float)gameTime.ElapsedGameTime.Seconds();
			auto cameraDistance = CAMERA_CUTSCENE_SPEED * deltaTime;

			camera->Move(Vector2{ cameraDistance, 0 });

			if (camera->GetBounds().X() >= openDoorPosition_x)
			{
				door->Open();
				currentState = State::OPENING_DOOR;
			}
			break;
		}

		case State::OPENING_DOOR:
		{
			auto &doorSprite = static_cast<AnimatedSprite&>(*door->GetSprite());
			
			if (doorSprite.AnimateComplete())
			{
				if (doorHitDirection == Direction::Left)
					player->WalkRight();
				else if (doorHitDirection == Direction::Right)
					player->WalkLeft();
				else // Handle edge cases where player may jump on top of door bbox before falling on ground
				{
					if (player->GetOriginPosition().x < door->GetOriginPosition().x)
						player->WalkRight();
					else
						player->WalkLeft();
				}

				playerDestination_x = player->GetPosition().x + WALK_DISTANCE;
				currentState = State::GOING_TO_NEXT_ROOM;
			}
			break;
		}

		case State::GOING_TO_NEXT_ROOM:
		{
			if (player->GetPosition().x >= playerDestination_x)
			{
				door->Close();
				player->Idle();
				currentState = State::CLOSING_DOOR;
			}
			break;
		}

		case State::CLOSING_DOOR:
		{
			auto &doorSprite = static_cast<AnimatedSprite&>(*door->GetSprite());

			if (doorSprite.AnimateComplete())
			{
				currentState = State::VIEWPORT_MOVING_SECOND_HALF;
			}
			break;
		}

		case State::VIEWPORT_MOVING_SECOND_HALF:
		{
			auto deltaTime = (float)gameTime.ElapsedGameTime.Seconds();
			auto cameraDistance = CAMERA_CUTSCENE_SPEED * deltaTime;

			if (camera->GetBounds().X() + cameraDistance > viewportDestination_x)
				cameraDistance = viewportDestination_x - camera->GetBounds().X();

			camera->Move(Vector2{ cameraDistance, 0 });

			if (camera->GetBounds().X() >= viewportDestination_x)
			{
				player->EnableControl(true);
				isComplete = true;
				stage.OnNotify(Subject::Empty(), NEXT_ROOM_CUTSCENE_ENDED);
			}
			break;
		}
	}
}
