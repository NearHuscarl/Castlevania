#pragma once

#include "../Body/CollisionData.h"

namespace Castlevania
{
	struct ObjectCollection;

	class ICollisionSystem
	{
	public:
		virtual CollisionData GetCollisionData() = 0;
		virtual void Update(ObjectCollection &objectCollection) = 0;
	};
}