#pragma once

#include "ICollisionResponseSystem.h"

namespace Castlevania
{
	class GameObject;

	class CollisionResponseSystem : public ICollisionResponseSystem
	{
	public:
		CollisionResponseSystem(GameObject &parent);

		virtual void Update(CollisionData collisionData) override;

	private:
		GameObject &parent;
	};
}