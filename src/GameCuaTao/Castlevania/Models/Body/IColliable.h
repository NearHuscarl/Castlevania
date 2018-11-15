#pragma once

#include "Direct2DGame/Base/Rect.h"
#include "Direct2DGame/Base/Vector2.h"
#include "../EntityType.h"

namespace Castlevania
{
	class IColliable
	{
	public:
		virtual EntityType GetType() = 0;
		virtual Vector2 GetPosition() = 0;
		virtual Rect GetBoundingBox() = 0;
	};
}