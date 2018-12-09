#include "SpawnArea.h"
#include "../UpdateData.h"

using namespace Castlevania;

SpawnArea::SpawnArea(EntityType spawnObjectType, ObjectFactory &objectFactory) :
	objectFactory{ objectFactory },
	GameObject{ EntityType::SpawnArea }
{
	this->spawnObjectType = spawnObjectType;
	Deactivate();
}

SpawnState SpawnArea::GetSpawnState()
{
	return spawnState;
}

void SpawnArea::SetSpawnGroupCount(int spawnGroup)
{
	this->spawnGroupCount = spawnGroup;
}

void SpawnArea::SetGroupSpawnTime(int groupSpawnTime)
{
	this->groupSpawnTime = groupSpawnTime;
}

void SpawnArea::SetSpawnTime(int spawnTime)
{
	this->spawnTime = spawnTime;
}

void SpawnArea::Activate()
{
	spawnState = SpawnState::ACTIVE;
}

void SpawnArea::Deactivate()
{
	spawnState = SpawnState::INACTIVE;
	groupSpawnTimer.Reset();
}

void SpawnArea::Update(GameTime gameTime, UpdateData &updateData)
{
	GameObject::Update(gameTime, updateData);

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
				spawnGroupCountLeft--;
			}
			if (spawnGroupCountLeft <= 0)
				StopSpawning();
			break;
	}
}

void SpawnArea::StartSpawning()
{
	spawnState = SpawnState::SPAWNING;
	spawnGroupCountLeft = spawnGroupCount;
}

void SpawnArea::StopSpawning()
{
	spawnState = SpawnState::ACTIVE;
	spawnTimer.Reset();
	groupSpawnTimer.Restart();
}
