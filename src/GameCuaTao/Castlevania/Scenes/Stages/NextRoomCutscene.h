#pragma once

#include "Direct2DGame/Extensions/Camera.h"
#include "Cutscene.h"
#include "../../Models/Characters/Player/Player.h"

namespace Castlevania
{
	class NextRoomCutscene : public Cutscene
	{
	public:
		NextRoomCutscene(Stage &stage, StageObject &stageObject, CollisionGrid &grid, Player &player);

		Door &GetDoor();
		void Update(UpdateData &updateData) override;

	private:
		enum class State;

		Player *player;
		Camera *camera;
		Door *door;
		Direction doorHitDirection;

		State currentState;
		float viewportDestination_x;
		float playerDestination_x;
		float openDoorPosition_x;

		void SetupCutscene();
	};
}