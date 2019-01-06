#pragma once

#include "MovementSystem.h"

namespace Castlevania
{
	// For objects in game that have weight (player, enemy)
	class EntityMovementSystem : public MovementSystem
	{
	public:
		EntityMovementSystem(GameObject &parent, float weight);

	private:
		GameObject &parent;
		float weight;

		void UpdateMovement(GameTime gameTime) override;
	};
}