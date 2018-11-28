#pragma once

#include "Direct2DGame/Graphics/Viewport.h"

namespace Castlevania
{
	struct ObjectCollection;

	struct UpdateData
	{
		Viewport viewport;
		ObjectCollection *objectCollection;

		static UpdateData Empty()
		{
			constexpr auto emptyData = UpdateData{};
			return emptyData;
		}

		bool IsEmpty()
		{
			return false; // TODO: check object collection size
		}
	};
}