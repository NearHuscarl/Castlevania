#pragma once

#include <unordered_map>
#include <string>
#include "../Models/EntityType.h"
#include "../Models/TriggerType.h"
#include "../Models/Facing.h"
#include "MapSettings.h"

namespace Castlevania
{
	const auto string2EntityType = std::unordered_map<std::string, EntityType>
	{
		{ "SpawnArea", EntityType::SpawnArea },
		{ "SpawnPoint", EntityType::SpawnPoint },
		{ "Player", EntityType::Player },
		{ "Bat", EntityType::Bat },
		{ "Cloud", EntityType::Cloud },
		{ "Brazier", EntityType::Brazier },
		{ "Candle", EntityType::Candle },
		{ "Zombie", EntityType::Zombie },
		{ "Panther", EntityType::Panther },
		{ "Fishman", EntityType::Fishman },
		{ "VampireBat", EntityType::VampireBat },
		{ "GiantBat", EntityType::GiantBat },
		{ "Whip", EntityType::Whip },
		{ "DaggerItem", EntityType::DaggerItem },
		{ "LargeHeart", EntityType::LargeHeart },
		{ "WhipPowerup", EntityType::WhipPowerup },
		{ "MoneyBag", EntityType::MoneyBag },
		{ "Castle", EntityType::Castle },
		{ "DirtBlock", EntityType::DirtBlock },
	};

	const auto string2TriggerType = std::unordered_map<std::string, TriggerType>
	{
		{ "NextMap", TriggerType::NEXT_MAP },
		{ "MoneyBagTrigger", TriggerType::MONEY_BAG_EASTER_EGG },
		{ "StairUp", TriggerType::STAIR_UP },
		{ "StairDown", TriggerType::STAIR_DOWN },
		{ "CastleEntrance", TriggerType::CASTLE_ENTRANCE },
	};

	const auto string2Facing = std::unordered_map<std::string, Facing>
	{
		{ "Left", Facing::Left },
		{ "Right", Facing::Right },
		{ "None", Facing::None },
	};

	const auto string2Map = std::unordered_map<std::string, Map>
	{
		{ "Intro", Map::INTRO },
		{ "Courtyard", Map::COURTYARD },
		{ "GreatHall", Map::GREAT_HALL },
		{ "Underground", Map::UNDERGROUND },
		{ "Playground", Map::PLAYGROUND },
	};
}