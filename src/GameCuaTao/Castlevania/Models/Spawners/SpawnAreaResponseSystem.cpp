#include "SpawnAreaResponseSystem.h"

using namespace Castlevania;

SpawnAreaResponseSystem::SpawnAreaResponseSystem(SpawnArea &parent) : parent{ parent }
{
}

void SpawnAreaResponseSystem::Update(UpdateData &updateData)
{
	auto collisionData = parent.GetBody().GetCollisionData();
	auto collideWithPlayer = false;

	for (auto result : collisionData.collisionResults)
	{
		auto type = (EntityType)result.collidedObject.GetType();

		switch (type)
		{
			case EntityType::Player:
				collideWithPlayer = true;
				break;
		}
	}

	switch (parent.GetSpawnState())
	{
		case SpawnState::ACTIVE:
			if (!collideWithPlayer)
				parent.Deactivate();
			break;

		case SpawnState::INACTIVE:
			if (collideWithPlayer)
				parent.Activate();
			break;
	}
}
