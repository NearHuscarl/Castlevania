#pragma once

#include "Direct2DGame/GameTime.h"
#include "Direct2DGame/Graphics/Viewport.h"

namespace Castlevania
{
	struct ObjectCollection;

	struct UpdateData
	{
		RectF viewport;
		ObjectCollection *objectCollection;

		static UpdateData Empty();
	};
}