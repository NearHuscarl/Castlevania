#include "PoisonResponseSystem.h"
#include "../../Models/UpdateData.h"
#include "../Items/Container.h"
#include "../Items/Fireball.h"
#include "../Characters/Enemies/Enemy.h"

using namespace Castlevania;

PoisonResponseSystem::PoisonResponseSystem(RangedWeapon &parent) : parent{ parent }
{
}

void PoisonResponseSystem::Update(UpdateData &updateData)
{
	auto collisionData = parent.GetBody().GetCollisionData();

	if (collisionData.collisionResults.size() == 0)
		return;

	for (auto result : collisionData.collisionResults)
	{
		auto objectId = (ObjectId)result.collidedObject.GetType();

		switch (objectId)
		{
			case ObjectId::Brazier:
				OnCollideWithBrazier(result);
				break;

			case ObjectId::Zombie:
			case ObjectId::Panther:
			case ObjectId::Fishman:
			case ObjectId::VampireBat:
			case ObjectId::GiantBat:
				OnCollideWithEnemy(result, *updateData.player);
				break;

			case ObjectId::Fireball:
				OnCollideWithFireball(result);
				break;
		}
	}
}

void PoisonResponseSystem::OnCollideWithBrazier(CollisionResult &result)
{
	auto &brazier = dynamic_cast<Container&>(result.collidedObject);

	brazier.OnBeingHit();
}

void PoisonResponseSystem::OnCollideWithEnemy(CollisionResult &result, Player &player)
{
	auto &enemy = dynamic_cast<Enemy&>(result.collidedObject);

	enemy.TakeDamage(parent.GetAttack());

	if (enemy.GetState() == ObjectState::DYING)
		player.AddExp(enemy.GetExp());
}

void PoisonResponseSystem::OnCollideWithFireball(CollisionResult &result)
{
	auto &fireball = dynamic_cast<Fireball&>(result.collidedObject);

	fireball.GetBody().Enabled(false);
	fireball.SetState(ObjectState::DYING);
}
