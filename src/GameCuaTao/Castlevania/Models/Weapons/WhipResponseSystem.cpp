#include "WhipResponseSystem.h"
#include "../../Models/UpdateData.h"
#include "../Items/Brazier.h"
#include "../Characters/Enemies/Enemy.h"
#include "../Characters/Player/Player.h"

using namespace Castlevania;

WhipResponseSystem::WhipResponseSystem(Whip &parent) : parent{ parent }
{
}

void WhipResponseSystem::Update(UpdateData &updateData)
{
	auto collisionData = parent.GetBody().GetCollisionData();
	auto &objectCollection = *updateData.objectCollection;

	if (collisionData.collisionResults.size() == 0)
		return;

	for (auto result : collisionData.collisionResults)
	{
		auto type = (EntityType)result.collidedObject.GetType();

		switch (type)
		{
			case EntityType::Brazier:
				OnCollideWithBrazier(result, objectCollection);
				break;

			case EntityType::Zombie:
			case EntityType::Panther:
			case EntityType::Fishman:
			case EntityType::VampireBat:
				OnCollideWithEnemy(result, *objectCollection.player);
				break;
		}
	}
}

void WhipResponseSystem::OnCollideWithBrazier(CollisionResult &result, ObjectCollection &objectCollection)
{
	auto &brazier = dynamic_cast<Brazier&>(result.collidedObject);

	objectCollection.entities.push_back(brazier.SpawnItem());
	brazier.OnBeingHit();
}

void WhipResponseSystem::OnCollideWithEnemy(CollisionResult &result, Player &player)
{
	auto &enemy = dynamic_cast<Enemy&>(result.collidedObject);

	enemy.TakeDamage(parent.GetAttack());

	if (enemy.GetState() == ObjectState::DYING)
		player.AddExp(enemy.GetExp());
}
