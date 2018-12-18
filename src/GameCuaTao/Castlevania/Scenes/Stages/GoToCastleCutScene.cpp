#include "GoToCastleCutScene.h"
#include "Stage.h"

using namespace Castlevania;

enum class GoToCastleCutscene::State
{
	WALKING_TO_CASTLE_GATE,
	WALKING_TO_NEXT_MAP,
};

GoToCastleCutscene::GoToCastleCutscene(Stage &stage, ObjectCollection &objectCollection) :
	Cutscene{ stage }
{
	player = objectCollection.player.get();

	for (auto &object : objectCollection.staticObjects)
	{
		if (object->GetId() != ObjectId::Trigger)
			continue;

		auto trigger = dynamic_cast<Trigger*>(object.get());

		if (trigger->GetTriggerType() == TriggerType::CASTLE_ENTRANCE)
			entranceTrigger = trigger;

		if (trigger->GetTriggerType() == TriggerType::NEXT_MAP)
			nextMapTrigger = trigger;
	}

	for (auto &object : objectCollection.foregroundObjects)
	{
		if (object->GetId() == ObjectId::Castle)
		{
			castle = object.get();
			break;
		}
	}

	// Remove objects before cutscene even started is not necessary
	// But I will leave it here to mimic the original game behaviour
	objectCollection.entities.clear();

	SetupCutscene();
}

void GoToCastleCutscene::SetupCutscene()
{
	playerOriginalSpeed = player->GetSpeed();

	player->SetSpeed(playerOriginalSpeed / 3);
	player->EnableControl(false);

	if (player->GetBoundingBox().right <= entranceTrigger->GetBoundingBox().right)
		player->WalkRight();
	else
		player->WalkLeft();

	nextMapTrigger->Enabled(true);

	currentState = State::WALKING_TO_CASTLE_GATE;
}

void GoToCastleCutscene::Update(GameTime gameTime)
{
	stage.UpdateGameObjects(gameTime);

	switch (currentState)
	{
		case State::WALKING_TO_CASTLE_GATE:
			if (player->GetBoundingBox().right <= entranceTrigger->GetBoundingBox().right - 5.0f)
			{
				if (player->GetFacing() == Facing::Left)
					player->WalkRight();

				castle->SetVisibility(true);
				currentState = State::WALKING_TO_NEXT_MAP;
			}
			break;

		case State::WALKING_TO_NEXT_MAP:
			if (player->GetNearbyObjects().nextMap != nullptr)
			{
				player->SetSpeed(playerOriginalSpeed);
				isComplete = true;
			}
			break;
	}
}
