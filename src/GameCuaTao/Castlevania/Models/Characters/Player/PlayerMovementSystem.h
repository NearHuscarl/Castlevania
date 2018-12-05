#pragma once

#include "../../Systems/Movement/MovementSystem.h"
#include "Player.h"

namespace Castlevania
{
	class PlayerMovementSystem : public MovementSystem
	{
	public:
		PlayerMovementSystem(Player &parent);
		void Update(GameTime gameTime) override;

	private:
		Player &parent;
	};
}