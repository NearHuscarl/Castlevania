#pragma once

#include <map>
#include <set>
#include "Direct2DGame/Base/Rect.h"
#include "../Models/GameObject.h"

namespace Castlevania
{
	constexpr auto NEXT_MAP = "NextMap";
	constexpr auto CHECKPOINT = "Checkpoint";

	const std::set<std::string> BOUNDARIES =
	{
		"LeftBorder",
		"RightBorder",
		"Ground",
	};

	const std::set<std::string> TRIGGERS =
	{
		NEXT_MAP,
	};

	const std::set<std::string> POSITIONS =
	{
		CHECKPOINT,
	};

	struct ObjectCollection
	{
		std::map<std::string, Rect> boundaries;
		std::map<std::string, Rect> triggers;
		std::map<std::string, Vector2> locations;
		std::vector<std::unique_ptr<GameObject>> entities;
	};
}