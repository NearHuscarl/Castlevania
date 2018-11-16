#pragma once

#include "Body/IColliable.h"
#include "EntityType.h"

namespace Castlevania
{
	class IGameObject : public IColliable
	{
	public:
		virtual EntityType GetType() = 0;
		virtual Vector2 GetVelocity() = 0;
	};
}