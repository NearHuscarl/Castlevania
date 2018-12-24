#include "HolyWaterResponseSystem.h"
#include "../../Models/Characters/Player/Player.h"
#include "../../Models/UpdateData.h"
#include "../Items/Container.h"
#include "../Items/Fireball.h"
#include "../Characters/Enemies/Enemy.h"

using namespace Castlevania;

HolyWaterResponseSystem::HolyWaterResponseSystem(HolyWater &parent) : parent{ parent }
{
}

void HolyWaterResponseSystem::Update(UpdateData &updateData)
{
	auto collisionData = parent.GetBody().GetCollisionData();

	if (collisionData.collisionResults.size() == 0)
		return;

	for (auto result : collisionData.collisionResults)
	{
		auto objectId = (ObjectId)result.collidedObject.GetType();

		switch (objectId)
		{
			case ObjectId::Boundary:
				OnCollideWithBoundary(result);
				break;

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

void HolyWaterResponseSystem::OnCollideWithBoundary(CollisionResult &result)
{
	if (result.direction == Direction::Top)
	{
		auto &boundary = dynamic_cast<GameObject&>(result.collidedObject);
		auto position = parent.GetPosition();

		position.y = boundary.GetPosition().y - parent.GetFrameRect().Height();
		parent.SetPosition(position);
		parent.StartFlaming();
	}
}

void HolyWaterResponseSystem::OnCollideWithBrazier(CollisionResult &result)
{
	auto &brazier = dynamic_cast<Container&>(result.collidedObject);

	brazier.OnBeingHit();
}

void HolyWaterResponseSystem::OnCollideWithEnemy(CollisionResult &result, Player &player)
{
	auto &enemy = dynamic_cast<Enemy&>(result.collidedObject);

	enemy.TakeDamage(parent.GetAttack());

	if (enemy.GetState() == ObjectState::DYING)
		player.AddExp(enemy.GetExp());
}

void HolyWaterResponseSystem::OnCollideWithFireball(CollisionResult &result)
{
	auto &fireball = dynamic_cast<Fireball&>(result.collidedObject);

	fireball.GetBody().Enabled(false);
	fireball.SetState(ObjectState::DYING);
}

