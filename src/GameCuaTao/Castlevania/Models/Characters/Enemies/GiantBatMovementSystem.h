#pragma once

#include "../../Systems/Movement/MovementSystem.h"
#include "GiantBat.h"

namespace Castlevania
{
	// For objects in game that have weight (player, enemy)
	class GiantBatMovementSystem : public MovementSystem
	{
	public:
		GiantBatMovementSystem(GiantBat &parent);
		void Update(GameTime gameTime) override;

	private:
		GiantBat &parent;

		void UpdateLinearMovement(float deltaTime);
		void UpdateParabolicMovement(float deltaTime);
	};
}