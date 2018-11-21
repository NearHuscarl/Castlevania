#pragma once

#include "../IReceiver.h"

namespace Castlevania
{
	struct ObjectCollection;

	class ICollisionResponseSystem : public IReceiver
	{
	public:
		virtual void Update(ObjectCollection &objectCollection) = 0;
		virtual ~ICollisionResponseSystem() {}
	};
}