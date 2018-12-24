#include "WeaponResponseSystem.h"
#include "../../Models/UpdateData.h"
#include "../Items/Container.h"
#include "../Items/Fireball.h"
#include "../Characters/Enemies/Enemy.h"
#include "../Characters/Player/Player.h"
#include "../Settings.h"
#include "../IAttackable.h"

using namespace Castlevania;

WeaponResponseSystem::WeaponResponseSystem(GameObject &parent, bool destroyOnHit) : parent{ parent }
{
	this->destroyOnHit = destroyOnHit;
}

void WeaponResponseSystem::Receive(int message)
{
	switch (message)
	{
		case WHIP_WITHDRAWN:
			hitEnemies.clear();
			break;
	}
}

void WeaponResponseSystem::Update(UpdateData &updateData)
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

void WeaponResponseSystem::OnCollideWithBrazier(CollisionResult &result)
{
	auto &brazier = dynamic_cast<Container&>(result.collidedObject);

	brazier.OnBeingHit();

	if (destroyOnHit)
		parent.Destroy();
}

void WeaponResponseSystem::OnCollideWithEnemy(CollisionResult &result, Player &player)
{
	auto weapon = dynamic_cast<IAttackable*>(&parent);

	if (weapon == nullptr)
		return;

	auto &enemy = dynamic_cast<Enemy&>(result.collidedObject);

	for (auto hitEnemy : hitEnemies)
	{
		if (hitEnemy == &enemy)
			return;
	}

	enemy.TakeDamage(weapon->GetAttack());

	if (enemy.GetState() == ObjectState::DYING)
		player.AddExp(enemy.GetExp());

	hitEnemies.push_back(&enemy);

	if (destroyOnHit)
		parent.Destroy();
}

void WeaponResponseSystem::OnCollideWithFireball(CollisionResult &result)
{
	auto &fireball = dynamic_cast<Fireball&>(result.collidedObject);

	fireball.GetBody().Enabled(false);
	fireball.SetState(ObjectState::DYING);

	if (destroyOnHit)
		parent.Destroy();
}
