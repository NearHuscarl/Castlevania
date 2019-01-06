#pragma once

#include "../../Systems/Movement/MovementSystem.h"
#include "Player.h"

namespace Castlevania
{
	class PlayerMovementSystem : public MovementSystem
	{
	public:
		PlayerMovementSystem(Player &parent);

	private:
		Player &parent;
		
		void UpdateMovement(GameTime gameTime) override;
	};
}