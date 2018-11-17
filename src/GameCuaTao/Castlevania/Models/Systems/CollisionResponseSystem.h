#pragma once

#include "../Body/CollisionData.h"

namespace Castlevania
{
	class GameObject;

	class CollisionResponseSystem
	{
	public:
		CollisionResponseSystem(GameObject &parent);

		virtual void Update(float deltaTime, CollisionData collisionData);

	private:
		GameObject &parent;
	};
}