#pragma once

#include <string>
#include "../../Utilities/MapSettings.h"

namespace Castlevania
{
	struct RespawnPoint
	{
		Map map;
		std::string checkpoint;
	};
}