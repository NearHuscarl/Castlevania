#pragma once

#include "Direct2DGame/GameTime.h"
#include "Direct2DGame/Extensions/Camera.h"
#include "../../Models/Characters/Player/Player.h"

namespace Castlevania
{
	class NextRoomCutscene
	{
	public:
		NextRoomCutscene(Player &player, Camera &camera, Door &door);

		Door &GetDoor();

		bool IsComplete();
		void Update(GameTime gameTime);

	private:
		enum class State;

		Player &player;
		Camera &camera;
		Door &door;
		Direction doorHitDirection;

		State currentState;
		float viewportDestination_x;
		float playerDestination_x;
		float openDoorPosition_x;

		bool isComplete;
	};
}