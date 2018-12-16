#pragma once

#include <unordered_map>
#include <string>
#include "../Models/ObjectId.h"
#include "../Models/TriggerType.h"
#include "../Models/Facing.h"
#include "MapSettings.h"

namespace Castlevania
{
	const auto string2EntityType = std::unordered_map<std::string, ObjectId>
	{
		{ "ViewportArea", ObjectId::ViewportArea },
		{ "BossFightArea", ObjectId::BossFightArea },
		{ "WaterArea", ObjectId::WaterArea },
		{ "SpawnArea", ObjectId::SpawnArea },
		{ "SpawnPoint", ObjectId::SpawnPoint },
		{ "Player", ObjectId::Player },
		{ "Bat", ObjectId::Bat },
		{ "Cloud", ObjectId::Cloud },
		{ "Brazier", ObjectId::Brazier },
		{ "Candle", ObjectId::Candle },
		{ "Zombie", ObjectId::Zombie },
		{ "Panther", ObjectId::Panther },
		{ "Fishman", ObjectId::Fishman },
		{ "VampireBat", ObjectId::VampireBat },
		{ "GiantBat", ObjectId::GiantBat },
		{ "Fireball", ObjectId::Fireball },
		{ "Whip", ObjectId::Whip },
		{ "DaggerItem", ObjectId::DaggerItem },
		{ "LargeHeart", ObjectId::LargeHeart },
		{ "SmallHeart", ObjectId::SmallHeart },
		{ "WhipPowerup", ObjectId::WhipPowerup },
		{ "BlueMoneyBag", ObjectId::BlueMoneyBag },
		{ "WhiteMoneyBag", ObjectId::WhiteMoneyBag },
		{ "RedMoneyBag", ObjectId::RedMoneyBag },
		{ "FlashingMoneyBag", ObjectId::FlashingMoneyBag },
		{ "Door", ObjectId::Door },
		{ "Castle", ObjectId::Castle },
		{ "DirtBlock", ObjectId::DirtBlock },
	};

	const auto string2TriggerType = std::unordered_map<std::string, TriggerType>
	{
		{ "StairUp", TriggerType::STAIR_UP },
		{ "StairDown", TriggerType::STAIR_DOWN },
		{ "NextMap", TriggerType::NEXT_MAP },
		{ "BossFight", TriggerType::BOSS_FIGHT },
		{ "CastleEntrance", TriggerType::CASTLE_ENTRANCE },
		{ "MoneyBagTrigger", TriggerType::MONEY_BAG_EASTER_EGG },
	};

	const auto string2Direction = std::unordered_map<std::string, Direction>
	{
		{ "Left", Direction::Left },
		{ "Top", Direction::Top },
		{ "Right", Direction::Right },
		{ "Bottom", Direction::Bottom },
		{ "None", Direction::None },
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