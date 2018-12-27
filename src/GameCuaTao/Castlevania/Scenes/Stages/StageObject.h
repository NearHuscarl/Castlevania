#pragma once

#include "../../Models/Spawners/SpawnArea.h"

namespace Castlevania
{
	struct StageObject
	{
		std::vector<std::unique_ptr<GameObject>> foregroundObjects;
		std::vector<std::unique_ptr<GameObject>> stageAreas;
		std::vector<std::unique_ptr<SpawnArea>> spawnAreas;
		std::map<std::string, Vector2> locations;
	};
}