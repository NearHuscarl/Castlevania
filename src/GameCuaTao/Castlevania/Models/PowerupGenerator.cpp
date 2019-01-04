#include <set>
#include "Direct2DGame/MathHelper.h"
#include "PowerupGenerator.h"
#include "Factories/ObjectFactory.h"

using namespace Castlevania;

constexpr auto COMMON_POWERUP = "COMMON_POWERUP";
constexpr auto UNCOMMON_POWERUP = "UNCOMMON_POWERUP";
constexpr auto RARE_POWERUP = "RARE_POWERUP";
constexpr auto ALTERNATE_POWERUP_CHANCE = 25;
constexpr auto ENEMY_POWERUP_SPAWN_CHANCE = 20;

// powerup rarity - spawn chance (%)
const auto POWERUP_SPAWN_CHANCES = std::unordered_map<std::string, int>
{
	{ COMMON_POWERUP, 70 },
	{ UNCOMMON_POWERUP, 25 },
	{ RARE_POWERUP, 5 },
};

const auto POWERUP_GROUP = std::unordered_map<std::string, std::set<ObjectId>>
{
	{
		COMMON_POWERUP,
		{
			ObjectId::RedMoneyBag,
			ObjectId::BlueMoneyBag,
			ObjectId::SmallHeart,
		},
	},
	{
		UNCOMMON_POWERUP,
		{
			ObjectId::WhiteMoneyBag,
			ObjectId::AxeItem,
			//ObjectId::BoomerangItem,
			ObjectId::DaggerItem,
			ObjectId::HolyWaterItem,
			ObjectId::LargeHeart,
		},
	},
	{
		RARE_POWERUP,
		{
			ObjectId::FlashingMoneyBag,
			ObjectId::Cross,
			ObjectId::InvisibleJar,
			ObjectId::PorkChop,
			ObjectId::Stopwatch,
			ObjectId::DoubleShot,
			//ObjectId::TripleShot,
		},
	},
};

PowerupGenerator::PowerupGenerator(ObjectFactory &objectFactory) : objectFactory{ objectFactory }
{
}

std::unique_ptr<Powerup> PowerupGenerator::Generate()
{
	if (!MathHelper::RandomPercent(ENEMY_POWERUP_SPAWN_CHANCE))
		return nullptr;

	auto powerupId = ObjectId{};
	auto spawnChanceResult = MathHelper::RandomBetween(1, 100);
	auto commonSpawnChance = POWERUP_SPAWN_CHANCES.at(COMMON_POWERUP);
	auto uncommonSpawnChance = POWERUP_SPAWN_CHANCES.at(UNCOMMON_POWERUP);
	auto rareSpawnChance = POWERUP_SPAWN_CHANCES.at(RARE_POWERUP);

	if (0 <= spawnChanceResult && spawnChanceResult <= commonSpawnChance)
	{
		powerupId = GetRandomPowerupType(COMMON_POWERUP);
	}
	else if (commonSpawnChance < spawnChanceResult && spawnChanceResult <= commonSpawnChance + uncommonSpawnChance)
	{
		powerupId = GetRandomPowerupType(UNCOMMON_POWERUP);
	}
	else if (commonSpawnChance + uncommonSpawnChance < spawnChanceResult && spawnChanceResult <= 100)
		powerupId = GetRandomPowerupType(RARE_POWERUP);

	return objectFactory.CreatePowerup(powerupId);
}

std::unique_ptr<Powerup> PowerupGenerator::Generate(ObjectId powerupId)
{
	if (GetGroup(powerupId) == COMMON_POWERUP && MathHelper::RandomPercent(ALTERNATE_POWERUP_CHANCE))
	{
		return objectFactory.CreatePowerup(GetRandomPowerupType(COMMON_POWERUP));
	}
	else
		return objectFactory.CreatePowerup(powerupId);
}

std::string PowerupGenerator::GetGroup(ObjectId powerupType)
{
	if (POWERUP_GROUP.at(COMMON_POWERUP).find(powerupType) != POWERUP_GROUP.at(COMMON_POWERUP).end())
		return COMMON_POWERUP;
	else if (POWERUP_GROUP.at(UNCOMMON_POWERUP).find(powerupType) != POWERUP_GROUP.at(UNCOMMON_POWERUP).end())
		return UNCOMMON_POWERUP;
	else if (POWERUP_GROUP.at(RARE_POWERUP).find(powerupType) != POWERUP_GROUP.at(RARE_POWERUP).end())
		return RARE_POWERUP;
	else
		return "";
}

ObjectId PowerupGenerator::GetRandomPowerupType(const std::string &rarity)
{
	return *MathHelper::RandomItem(
		POWERUP_GROUP.at(rarity).begin(),
		POWERUP_GROUP.at(rarity).end());
}
