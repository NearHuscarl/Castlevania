#pragma once

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