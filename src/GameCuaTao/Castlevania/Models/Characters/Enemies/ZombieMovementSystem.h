#pragma once

#include "../../Systems/Movement/MovementSystem.h"
#include "Zombie.h"

namespace Castlevania
{
	class ZombieMovementSystem : public MovementSystem
	{
	public:
		ZombieMovementSystem(Zombie &parent);
		void Update(GameTime gameTime) override;

	private:
		Zombie &parent;
	};
}