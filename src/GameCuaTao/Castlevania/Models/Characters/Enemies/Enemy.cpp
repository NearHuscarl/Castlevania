#include "Enemy.h"
#include "../../Items/Powerup.h"
#include "../../UpdateData.h"
#include "../../Settings.h"
#include "../../../Utilities/CollisionGrid.h"

using namespace Castlevania;

Enemy::Enemy(ObjectId type) : GameObject{ type }
{
}

Health &Enemy::GetHealthRef()
{
	return health;
}

void Enemy::SetHealth(int value)
{
	health = Health{ value };
}

int Enemy::GetAttack()
{
	return attack;
}

void Enemy::SetAttack(int value)
{
	attack = value;
}

void Enemy::SetExp(int value)
{
	exp = value;
}

int Enemy::GetExp()
{
	return exp;
}

void Enemy::SetPowerupGenerator(std::unique_ptr<PowerupGenerator> powerupGenerator)
{
	this->powerupGenerator = std::move(powerupGenerator);
}

void Enemy::Update(UpdateData &updateData)
{
	if (!updateData.isStopwatchActive)
		GameObject::Update(updateData);
	else
		if (renderingSystem != nullptr && state == ObjectState::DYING)
			renderingSystem->Update(updateData.gameTime); // Update hit effect

	health.Update();

	auto viewport = updateData.viewport;

	if (!viewport.Contains(GetBoundingBox()))
		state = ObjectState::DEAD;
}

void Enemy::TakeDamage(int damage)
{
	if (health.Value() - damage <= 0)
		Die();
	
	health.Add(-damage);
	SendMessageToSystems(TAKING_DAMAGE);
}

void Enemy::Die()
{
	SetState(ObjectState::DYING);
	body.Enabled(false);
	Detach<IMovementSystem>();
	SpawnItem();
}

void Enemy::SpawnItem()
{
	if (powerupGenerator == nullptr)
		return;

	auto item = powerupGenerator->Generate();

	if (item == nullptr)
		return;

	auto spawnedPosition = Vector2{ GetOriginPosition().x, position.y };

	item->SetPosition(spawnedPosition);
	item->Spawn();
	collisionGrid->Add(std::move(item), CollisionObjectType::Entity);
}