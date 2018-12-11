#include "SpawnPoint.h"
#include "../UpdateData.h"
#include "../Factories/ObjectFactory.h"

using namespace Castlevania;

SpawnPoint::SpawnPoint(EntityType spawnObjectType, ObjectFactory &objectFactory) :
	GameObject{ EntityType::SpawnPoint },
	objectFactory{ objectFactory }
{
	this->spawnObjectType = spawnObjectType;
}

void SpawnPoint::Activate()
{
	spawnState = SpawnState::ACTIVE;
}

void SpawnPoint::Deactivate()
{
	spawnState = SpawnState::INACTIVE;
}

SpawnState SpawnPoint::GetSpawnState()
{
	return spawnState;
}

void SpawnPoint::Update(GameTime gameTime, UpdateData &updateData)
{
	GameObject::Update(gameTime, updateData);
	auto viewport = updateData.viewport;

	switch (spawnState)
	{
		case SpawnState::ACTIVE:
			if (!viewport.Contains(GetFrameRect()))
				Deactivate();
			break;

		case SpawnState::INACTIVE:
			if (viewport.Contains(GetFrameRect()))
			{
				Activate();
				auto object = objectFactory.CreateEnemy(spawnObjectType);
				auto objectCollection = updateData.objectCollection;

				object->SetPosition(position);
				object->SetFacing(facing);
				objectCollection->entities.push_back(std::move(object));
			}
			break;
	}
}
