#include "Enemy.h"
#include "../../UpdateData.h"
#include "../../Settings.h"

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
}
