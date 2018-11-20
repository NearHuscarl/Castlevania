#pragma once

#include "../../Systems/Movement/IMovementSystem.h"
#include "Player.h"

namespace Castlevania
{
	class PlayerMovementSystem : public IMovementSystem
	{
	public:
		PlayerMovementSystem(Player &parent);

		Vector2 GetDistance() override;
		void SetDistance(Vector2 distance) override;
		void Update(float deltaTime) override;

	private:
		Player &parent;
		Vector2 distance; // estimated distance next frame
	};
}