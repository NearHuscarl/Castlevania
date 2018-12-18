#include "DaggerResponseSystem.h"
#include "../../Models/UpdateData.h"
#include "../Characters/Enemies/Enemy.h"
#include "../Items/Container.h"

using namespace Castlevania;

DaggerResponseSystem::DaggerResponseSystem(GameObject &parent) : parent{ parent }
{
}

void DaggerResponseSystem::Update(UpdateData &updateData)
{
	auto &objectCollection = *updateData.objectCollection;
	auto collisionData = parent.GetBody().GetCollisionData();

	if (collisionData.collisionResults.size() == 0)
		return;

	for (auto result : collisionData.collisionResults)
	{
		auto objectId = (ObjectId)result.collidedObject.GetType();

		switch (objectId)
		{
			case ObjectId::Brazier:
				OnCollideWithBrazier(result, objectCollection);
				break;

			case ObjectId::Zombie:
			case ObjectId::Panther:
			case ObjectId::Fishman:
			case ObjectId::VampireBat:
			case ObjectId::GiantBat:
				OnCollideWithEnemy(result, *objectCollection.player);
				break;
		}
	}
}

void DaggerResponseSystem::OnCollideWithBrazier(CollisionResult &result, ObjectCollection &objectCollection)
{
	auto &brazier = dynamic_cast<Container&>(result.collidedObject);

	brazier.OnBeingHit();
	parent.Destroy();
}

void DaggerResponseSystem::OnCollideWithEnemy(CollisionResult &result, Player &player)
{
	auto &enemy = dynamic_cast<Enemy&>(result.collidedObject);

	enemy.TakeDamage(2); // TODO: inherit IAttackable

	if (enemy.GetState() == ObjectState::DYING)
		player.AddExp(enemy.GetExp());

	parent.Destroy();
}
