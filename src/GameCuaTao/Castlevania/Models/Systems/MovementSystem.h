#pragma once

#include "IMovementSystem.h"

namespace Castlevania
{
	class GameObject;

	class MovementSystem : public IMovementSystem
	{
	public:
		MovementSystem(GameObject &parent);

		Vector2 GetDistance() override;
		void Update() override;

	private:
		GameObject &parent;
		Vector2 distance; // estimated distance next frame
	};
}