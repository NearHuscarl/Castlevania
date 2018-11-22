#pragma once

#include "Direct2DGame/Extensions/Sprites/IDrawable.h"

namespace Castlevania
{
	class IEffect : public IDrawable
	{
	public:
		virtual void Show(Vector2 position) = 0;
		virtual bool IsFinished() = 0;
	};
}