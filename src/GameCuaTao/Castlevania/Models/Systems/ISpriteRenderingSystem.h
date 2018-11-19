#pragma once

#include "IRenderingSystem.h"

namespace Castlevania
{
	class ISpriteRenderingSystem : public IRenderingSystem
	{
	public:
		virtual Sprite &GetSprite() = 0;
	};
}
