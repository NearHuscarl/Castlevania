#include "IntroCutscene.h"
#include "Stage.h"
#include "StageEvent.h"

using namespace Castlevania;

constexpr auto WAITING_TIME = 4000;

enum class IntroCutscene::State
{
	GOING_TO_THE_GATE,
	LOOKING_AT_THE_CASTLE,
};

IntroCutscene::IntroCutscene(Stage &stage, CollisionGrid &grid, Player &player) : Cutscene{ stage }, player{ player }
{
	grid.GetCellsFromBoundingBox(stage.GetCamera()->GetBounds(), [&](CollisionCell &cell, int col, int row)
	{
		auto &objects = cell.GetObjects();

		for (auto &object : objects.staticObjects)
		{
			if (object->GetId() != ObjectId::Trigger)
				continue;

			auto trigger = dynamic_cast<Trigger*>(object.get());

			if (trigger->GetTriggerType() == TriggerType::NEXT_MAP)
				nextMapTrigger = trigger;
		}
	});

	playerOriginalSpeed = player.GetSpeed();

	player.SetSpeed(playerOriginalSpeed / 1.75f);
	player.EnableControl(false);
	player.WalkLeft();

	gatePosition = Vector2{
		stage.GetCamera()->GetBounds().Width() / 2 + 3,
		player.GetPosition().y };
	currentState = State::GOING_TO_THE_GATE;
}

void IntroCutscene::Update(UpdateData &updateData)
{
	stage.UpdateGameObjects(updateData);

	switch (currentState)
	{
		case State::GOING_TO_THE_GATE:
			if (player.GetOriginPosition().x >= gatePosition.x)
				player.WalkLeft();
			else
			{
				player.TurnBackward();
				transitionTimer.Start();
				currentState = State::LOOKING_AT_THE_CASTLE;
			}
			break;

		case State::LOOKING_AT_THE_CASTLE:
			if (transitionTimer.ElapsedMilliseconds() > WAITING_TIME)
			{
				player.SetSpeed(playerOriginalSpeed);
				player.Idle();
				player.SetFacing(Facing::Right);
				nextMapTrigger->GetBody().Enabled(true);
				isFinished = true;
			}
			break;
	}
}

void IntroCutscene::Draw(SpriteExtensions &spriteBatch)
{
	// Dont draw the one frame right before changing cutscene where simon is in IDLE animation
	if (!isFinished)
	{
		Cutscene::Draw(spriteBatch);
	}
}
