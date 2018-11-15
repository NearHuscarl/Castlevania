#pragma once

#include "Body/IColliable.h"

namespace Castlevania
{
	class IDynamic : public IColliable
	{
	public:
		virtual Vector2 GetVelocity() = 0;
	};
}