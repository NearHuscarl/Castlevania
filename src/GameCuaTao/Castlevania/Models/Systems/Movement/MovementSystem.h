#pragma once

#include "IMovementSystem.h"

namespace Castlevania
{
	class GameObject;

	// Basic movement system: distance = velocity * deltaTime
	class MovementSystem : public IMovementSystem
	{
	public:
		void Enabled(bool value) override;
		bool Enabled() override;

		Vector2 GetDistance() override;
		void SetDistance(Vector2 distance) override;

		virtual void Receive(int message) override {};
		void Update(GameTime gameTime) override;

	protected:
		bool enabled;
		Vector2 distance; // estimated distance to move
		
		virtual void UpdateMovement(GameTime gameTime) = 0;
	};
}