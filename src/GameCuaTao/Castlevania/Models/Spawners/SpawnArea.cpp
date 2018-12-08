#include "Direct2DGame/MathHelper.h"
#include "SpawnArea.h"
#include "../UpdateData.h"
#include "../Factories/ObjectFactory.h"

using namespace Castlevania;

SpawnArea::SpawnArea(ObjectFactory &objectFactory) :
	objectFactory{ objectFactory },
	GameObject{ EntityType::SpawnArea }
{
	this->spawnedObjectType = spawnedObjectType;
	spawnState = SpawnState::INACTIVE;
}

void SpawnArea::SetSpawnGroupCount(int minSpawnGroup, int maxSpawnGroup)
{
	this->minSpawnGroup = minSpawnGroup;

	if (maxSpawnGroup == 0)
		this->maxSpawnGroup = minSpawnGroup;
	else
		this->maxSpawnGroup = maxSpawnGroup;
}

void SpawnArea::SetGroupSpawnTime(int minGroupSpawnTime, int maxGroupSpawnTime)
{
	this->minGroupSpawnTime = minGroupSpawnTime;
	this->maxGroupSpawnTime = maxGroupSpawnTime;
}

void SpawnArea::SetSpawnTime(int spawnTime)
{
	this->spawnTime = spawnTime;
}

void SpawnArea::Activate()
{
	ResetGroupSpawnTimer();
	spawnState = SpawnState::ACTIVE;
}

void SpawnArea::Deactivate()
{
	spawnState = SpawnState::INACTIVE;
}

void SpawnArea::Update(GameTime gameTime, UpdateData &updateData)
{
	auto objectCollection = updateData.objectCollection;
	auto player = objectCollection->player;
	auto spawnAreaBbox = GetBoundingBox();

	switch (spawnState)
	{
		case SpawnState::ACTIVE:
			if (!player->GetBoundingBox().TouchesOrIntersects(spawnAreaBbox))
			{
				Deactivate();
				break;
			}
			if (groupSpawnTimer.ElapsedMilliseconds() > groupSpawnTime)
				StartSpawning();
			break;

		case SpawnState::SPAWNING:
			if (spawnTimer.ElapsedMilliseconds() > spawnTime)
			{
				SpawnObject(*objectCollection, updateData.viewport);
				spawnTimer.Restart();
				groupSpawnCount--;
			}
			if (groupSpawnCount <= 0)
				StopSpawning();
			break;

		case SpawnState::INACTIVE:
			if (player->GetBoundingBox().TouchesOrIntersects(spawnAreaBbox))
				Activate();
			break;
	}
}

void SpawnArea::StartSpawning()
{
	groupSpawnCount = MathHelper::RandomBetween(minSpawnGroup, maxSpawnGroup);
	spawnState = SpawnState::SPAWNING;
	spawnTimer.Start();
}

void SpawnArea::StopSpawning()
{
	spawnState = SpawnState::ACTIVE;
	spawnTimer.Reset();
	ResetGroupSpawnTimer();
}

void SpawnArea::ResetGroupSpawnTimer()
{
	groupSpawnTime = MathHelper::RandomBetween(minGroupSpawnTime, maxGroupSpawnTime);
	groupSpawnTimer.Restart();
}
