#pragma once

#include "../../Systems/Movement/MovementSystem.h"
#include "Panther.h"

namespace Castlevania
{
	class PantherMovementSystem : public MovementSystem
	{
	public:
		PantherMovementSystem(Panther &parent);

		void Receive(int message) override;
		void Update(GameTime gameTime) override;

	private:
		Panther &parent;
	};
}