#pragma once

#include "ICollisionResponseSystem.h"

namespace Castlevania
{
	class GameObject;

	class CollisionResponseSystem : public ICollisionResponseSystem
	{
	public:
		CollisionResponseSystem(GameObject &parent);

		virtual void Update(ObjectCollection &objectCollection) override;

	private:
		GameObject &parent;
	};
}