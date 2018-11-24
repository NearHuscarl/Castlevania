#pragma once

#include <map>
#include <set>
#include "../RectangleObject.h"

namespace Castlevania
{
	constexpr auto BOUNDARY = "Boundary";
	constexpr auto TRIGGER = "Trigger";
	constexpr auto POSITION = "Position";
	constexpr auto OBJECT = "Object";

	struct ObjectCollection
	{
		std::vector<std::unique_ptr<RectangleObject>> boundaries;
		std::vector<std::unique_ptr<RectangleObject>> triggers;
		std::vector<std::unique_ptr<GameObject>> entities;
		std::map<std::string, Vector2> locations;
	};
}