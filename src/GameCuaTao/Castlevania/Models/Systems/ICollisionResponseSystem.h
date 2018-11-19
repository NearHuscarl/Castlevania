#pragma once

#include "Direct2DGame/Extensions/Collisions/Body/CollisionData.h"

namespace Castlevania
{
	struct ObjectCollection;

	class ICollisionResponseSystem
	{
	public:
		virtual void Update(ObjectCollection &objectCollection) = 0;
	};
}