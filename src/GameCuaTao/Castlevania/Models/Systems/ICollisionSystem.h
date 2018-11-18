#pragma once

#include "Direct2DGame/Extensions/Collisions/Body/CollisionData.h"

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