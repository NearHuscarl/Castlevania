#pragma once

#include "Direct2DGame/Extensions/Sprites/IDrawable.h"
#include "Direct2DGame/IUpdateable.h"

namespace Castlevania
{
	class IEffect : public IUpdateable, public IDrawable
	{
	public:
		virtual void Show(Vector2 position) = 0;
		virtual bool IsFinished() = 0;
	};
}