#include "Direct2DGame/MathHelper.h"
#include "SpawnArea.h"
#include "../UpdateData.h"
#include "../Factories/ObjectFactory.h"
#include "../../Utilities/CppExtensions.h"
#include "../../Utilities/TypeConverter.h"

using namespace Castlevania;

SpawnArea::SpawnArea(ObjectId spawnObjectType, ObjectFactory &objectFactory) :
	objectFactory{ objectFactory },
	GameObject{ ObjectId::SpawnArea }
{
	this->spawnObjectType = spawnObjectType;

	this->directionChances = std::map<Direction, float>
	{
		{ Direction::Left, 50.0f },
		{ Direction::Top, 0.0f },
		{ Direction::Right, 50.0f },
		{ Direction::Bottom, 0.0f },
	};

	this->groupCountChances = std::map<int, float>
	{
		{ 1, 100.0f },
	};

	Deactivate();
}

SpawnState SpawnArea::GetSpawnState()
{
	return spawnState;
}

void SpawnArea::SetGroupSpawnTime(int groupSpawnTime)
{
	this->groupSpawnTime = groupSpawnTime;
}

void SpawnArea::SetSpawnTime(int spawnTime)
{
	this->spawnTime = spawnTime;
}

// config format similar to SetGroupCountChances()
void SpawnArea::SetDirectionChances(std::string directionChancesConfig)
{
	auto directionChancesInfo = Split(directionChancesConfig, '-');
	auto directionChances = std::map<Direction, float>{};

	for (auto directionChance : directionChancesInfo)
	{
		auto directionChanceInfo = Split(directionChance, ':');
		auto direction = string2Direction.at(directionChanceInfo[0]);
		auto directionChance = std::stof(directionChanceInfo[1]);

		directionChances[direction] = directionChance;
	}

	SetDirectionChances(directionChances);
}

void SpawnArea::SetDirectionChances(std::map<Direction, float> directionChances)
{
	this->directionChances = directionChances;
}

//SpawnGroup format:
//		"3:100" - Spawn a group of 3 zombies 100 % of the time
//		"1:20-2:50-3:30"
//			- 20% chance to spawn 1 zombie
//			- 50% chance to spawn a group of 2 zombies
//			- 30% chance to spawn a group of 3 zombies
void SpawnArea::SetGroupCountChances(std::string groupCountChancesConfig)
{
	auto groupCountChancesInfo = Split(groupCountChancesConfig, '-');
	auto groupCountChances = std::map<int, float>{};

	for (auto groupCountChance : groupCountChancesInfo)
	{
		auto groupCountChanceInfo = Split(groupCountChance, ':');
		auto groupCount = std::stoi(groupCountChanceInfo[0]);
		auto groupCountChance = std::stof(groupCountChanceInfo[1]);

		groupCountChances[groupCount] = groupCountChance;
	}

	SetGroupCountChances(groupCountChances);
}

void SpawnArea::SetGroupCountChances(std::map<int, float> groupCountChances)
{
	this->groupCountChances = groupCountChances;
}

void SpawnArea::Activate()
{
	spawnState = SpawnState::ACTIVE;
}

void SpawnArea::Deactivate()
{
	groupSpawnTimer.Reset();
	spawnState = SpawnState::INACTIVE;
}

void SpawnArea::Update(UpdateData &updateData)
{
	GameObject::Update(updateData);

	switch (spawnState)
	{
		case SpawnState::ACTIVE:
			if (groupSpawnTimer.ElapsedMilliseconds() > groupSpawnTime || !groupSpawnTimer.IsRunning())
				StartSpawning();
			break;

		case SpawnState::SPAWNING:
			if (spawnTimer.ElapsedMilliseconds() > spawnTime || !spawnTimer.IsRunning())
			{
				SpawnObject(updateData);
				spawnTimer.Restart();
				spawnGroupCount--;
			}
			if (spawnGroupCount <= 0)
				StopSpawning();
			break;
	}
}

void SpawnArea::StartSpawning()
{
	for (auto const &[groupCount, chance] : groupCountChances)
	{
		if (MathHelper::RandomPercent(chance))
		{
			spawnGroupCount = groupCount;
			break;
		}
	}

	spawnState = SpawnState::SPAWNING;
}

void SpawnArea::StopSpawning()
{
	spawnTimer.Reset();
	groupSpawnTimer.Restart();
	spawnState = SpawnState::ACTIVE;
}
