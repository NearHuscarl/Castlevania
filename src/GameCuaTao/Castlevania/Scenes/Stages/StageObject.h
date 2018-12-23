#pragma once

#include "../../Models/GameObject.h"

namespace Castlevania
{
	struct StageObject
	{
		std::vector<std::unique_ptr<GameObject>> foregroundObjects;
		std::vector<std::unique_ptr<GameObject>> stageAreas;
		std::vector<std::unique_ptr<GameObject>> spawnAreas;
		std::map<std::string, Vector2> checkpoints;
	};
}