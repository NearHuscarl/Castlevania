#pragma once

#include "Direct2DGame/Extensions/Collisions/Body/Body.h"

namespace Castlevania
{
	class IGameObject : public IColliable
	{
	public:
		virtual Body &GetBody() = 0;
	};
}