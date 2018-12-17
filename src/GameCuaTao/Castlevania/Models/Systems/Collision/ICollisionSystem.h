#pragma once

#include "../IReceiver.h"

namespace Castlevania
{
	struct UpdateData;

	class ICollisionSystem : public IReceiver
	{
	public:
		virtual void Update(UpdateData &updateData) = 0;
		virtual ~ICollisionSystem() {}
	};
}