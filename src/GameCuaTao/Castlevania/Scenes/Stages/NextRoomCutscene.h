#pragma once

#include "Direct2DGame/Extensions/Camera.h"
#include "Cutscene.h"
#include "../../Models/Characters/Player/Player.h"
#include "../../Models/Factories/ObjectCollection.h"

namespace Castlevania
{
	class NextRoomCutscene : public Cutscene
	{
	public:
		NextRoomCutscene(Stage &stage, ObjectCollection &objectCollection);

		Door &GetDoor();
		void Update(GameTime gameTime) override;

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