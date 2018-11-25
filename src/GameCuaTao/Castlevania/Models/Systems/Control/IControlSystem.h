#pragma once

#include "../IReceiver.h"

namespace Castlevania
{
	class IControlSystem : public IReceiver
	{
	public:
		virtual void Update() = 0;
		virtual ~IControlSystem() {}
	};
}