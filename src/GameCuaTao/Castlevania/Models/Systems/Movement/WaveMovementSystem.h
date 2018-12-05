#pragma once

#include "MovementSystem.h"

namespace Castlevania
{
	class GameObject;

	enum class Axis
	{
		X,
		Y,
	};

	// Basic movement system: distance = velocity * deltaTime
	class WaveMovementSystem : public MovementSystem
	{
	public:
		WaveMovementSystem(GameObject &parent);

		void SetMoveAxis(Axis axis);
		void Update(GameTime gameTime) override;

	private:
		GameObject &parent;
		float linearVelocity;
		float angularVelocity;
		Axis moveAxis;
	};
}
