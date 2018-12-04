#pragma once

#include "Direct2DGame/GameTime.h"
#include "Direct2DGame/Graphics/Viewport.h"
#include "Factories/ObjectCollection.h"

namespace Castlevania
{
	struct UpdateData
	{
		RectF viewport;
		ObjectCollection *objectCollection;

		static UpdateData Empty();
	};
}