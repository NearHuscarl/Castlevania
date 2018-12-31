#pragma once

#include "../../Models/Spawners/SpawnArea.h"
#include "../../Models/Checkpoint.h"

namespace Castlevania
{
	struct StageObject
	{
		std::vector<std::unique_ptr<GameObject>> stageAreas;
		std::map<std::string, Checkpoint> locations;
	};
}