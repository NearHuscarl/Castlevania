#pragma once

#include "Direct2DGame/Extensions/Animations/AnimatedSprite.h"
#include "IRenderingSystem.h"

namespace Castlevania
{
	class AnimatedObject;

	class IAnimationRenderingSystem : public IRenderingSystem
	{
	public:
		virtual AnimatedSprite &GetSprite() = 0;
	};
}
