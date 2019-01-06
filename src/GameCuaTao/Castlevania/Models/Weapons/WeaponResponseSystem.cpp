#include "WeaponResponseSystem.h"
#include "../../Models/UpdateData.h"
#include "../Items/BreakableWall.h"
#include "../Items/Container.h"
#include "../Characters/Enemies/Enemy.h"
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
		case WEAPON_WITHDRAWN:
			hitObjects.clear();
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
			case ObjectId::Candle:
			case ObjectId::BreakableBlock:
				OnCollideWithContainer(result);
				break;

			case ObjectId::BreakableWall:
				OnCollideWithBreakableWall(result);
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

void WeaponResponseSystem::OnCollideWithContainer(CollisionResult &result)
{
	auto &container = dynamic_cast<Container&>(result.collidedObject);

	container.OnBeingHit();

	if (destroyOnHit)
		parent.Destroy();
}

void WeaponResponseSystem::OnCollideWithBreakableWall(CollisionResult &result)
{
	if (parent.GetId() != ObjectId::Whip)
		return;

	auto &breakableWall = dynamic_cast<BreakableWall&>(result.collidedObject);

	for (auto hitObject : hitObjects)
	{
		if (hitObject == &breakableWall)
			return;
	}

	hitObjects.push_back(&breakableWall);
	breakableWall.TakeDamage();
}

void WeaponResponseSystem::OnCollideWithEnemy(CollisionResult &result, Player &player)
{
	auto weapon = dynamic_cast<IAttackable*>(&parent);

	if (weapon == nullptr)
		return;

	auto &enemy = dynamic_cast<Enemy&>(result.collidedObject);

	for (auto hitObject : hitObjects)
	{
		if (hitObject == &enemy)
			return;
	}

	hitObjects.push_back(&enemy);
	enemy.TakeDamage(weapon->GetAttack());

	if (enemy.GetState() == ObjectState::DYING)
		player.AddExp(enemy.GetExp());

	if (destroyOnHit)
		parent.Destroy();
}

void WeaponResponseSystem::OnCollideWithFireball(CollisionResult &result)
{
	auto &fireball = dynamic_cast<GameObject&>(result.collidedObject);

	fireball.GetBody().Enabled(false);
	fireball.SetState(ObjectState::DYING);

	if (destroyOnHit)
		parent.Destroy();
}
