#pragma once

#include <map>
#include <set>
#include "Direct2DGame/Base/Rect.h"
#include "../Models/GameObject.h"

namespace Castlevania
{
	constexpr auto BOUNDARY = "Boundary";
	constexpr auto TRIGGER = "Trigger";
	constexpr auto POSITION = "Position";
	constexpr auto OBJECT = "Object";

	struct ObjectCollection
	{
		std::vector<std::unique_ptr<GameObject>> boundaries;
		std::vector<std::unique_ptr<GameObject>> triggers;
		std::vector<std::unique_ptr<GameObject>> entities;
		std::map<std::string, Vector2> locations;
	};
}