#pragma once

#include "Direct2DGame/Extensions/Collisions/Body/CollisionData.h"

namespace Castlevania
{
	class ICollisionResponseSystem
	{
	public:
		virtual void Update(CollisionData collisionData) = 0;
	};
}