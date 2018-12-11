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

		void Update(GameTime gameTime);

	private:
		Player &player;
		Camera &camera;
		Door &door;
	};
}