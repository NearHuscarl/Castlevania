#include "Enemy.h"
#include "../../UpdateData.h"
#include "../../Settings.h"

using namespace Castlevania;

Enemy::Enemy(ObjectId type) : GameObject{ type }
{
}

int &Enemy::GetHealthRef()
{
	return health;
}

void Enemy::SetHealth(int health)
{
	this->health = health;
}

int Enemy::GetAttack()
{
	return attack;
}

void Enemy::SetAttack(int attack)
{
	this->attack = attack;
}

void Enemy::SetExp(int exp)
{
	this->exp = exp;
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

	auto viewport = updateData.viewport;

	if (!viewport.Contains(GetBoundingBox()))
		state = ObjectState::DEAD;
}

void Enemy::TakeDamage(int damage)
{
	health -= damage;

	if (health <= 0)
		Die();
	
	SendMessageToSystems(TAKING_DAMAGE);
}

void Enemy::Die()
{
	SetState(ObjectState::DYING);
	body.Enabled(false);
	Detach<IMovementSystem>();
}
