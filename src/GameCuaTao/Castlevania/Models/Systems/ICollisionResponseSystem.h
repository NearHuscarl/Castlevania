#pragma once

#include "../Body/CollisionData.h"

namespace Castlevania
{
	class ICollisionResponseSystem
	{
	public:
		virtual void Update(CollisionData collisionData) = 0;
	};
}