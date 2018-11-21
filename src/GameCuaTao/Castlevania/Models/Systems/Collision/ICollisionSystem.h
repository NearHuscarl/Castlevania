#pragma once

#include "../IReceiver.h"

namespace Castlevania
{
	struct ObjectCollection;

	class ICollisionSystem : public IReceiver
	{
	public:
		virtual void Update(ObjectCollection &objectCollection) = 0;
		virtual ~ICollisionSystem() {}
	};
}