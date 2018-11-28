#pragma once

#include "IMovementSystem.h"

namespace Castlevania
{
	class GameObject;

	// Basic movement system: distance = velocity * deltaTime
	class MovementSystem : public IMovementSystem
	{
	public:
		MovementSystem(GameObject &parent);

		Vector2 GetDistance() override;
		void SetDistance(Vector2 distance) override;

		virtual void Receive(int message) override {};

		void Update(GameTime gameTime) override;

	private:
		GameObject &parent;
		Vector2 distance; // estimated distance to move
	};
}