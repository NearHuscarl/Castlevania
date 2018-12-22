#include "SpawnPoint.h"
#include "../UpdateData.h"
#include "../Factories/ObjectFactory.h"
#include "../../Utilities/CollisionGrid.h"

using namespace Castlevania;

SpawnPoint::SpawnPoint(ObjectId spawnObjectType, ObjectFactory &objectFactory) :
	GameObject{ ObjectId::SpawnPoint },
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

void SpawnPoint::Update(UpdateData &updateData)
{
	GameObject::Update(updateData);
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

				object->SetPosition(position);
				object->SetFacing(facing);
				collisionGrid->Add(std::move(object), CollisionObjectType::Entity);
			}
			break;
	}
}
