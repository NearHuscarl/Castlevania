#pragma once

#include "IMovementSystem.h"
#include "../Characters/Player/Player.h"

namespace Castlevania
{
	class GameObject;

	constexpr auto FALL_SPEED = 1000.0f; // TODO: put in xml

	class PlayerMovementSystem : public IMovementSystem
	{
	public:
		PlayerMovementSystem(Player &parent);

		Vector2 GetDistance() override;
		void Update(float deltaTime) override;

	private:
		Player &parent;
		Vector2 distance; // estimated distance next frame
	};
}