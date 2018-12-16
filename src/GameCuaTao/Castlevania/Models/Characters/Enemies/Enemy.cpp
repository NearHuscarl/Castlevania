#include "Enemy.h"
#include "../../UpdateData.h"

using namespace Castlevania;

Enemy::Enemy(ObjectId type) : GameObject{ type }
{
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

void Enemy::Update(GameTime gameTime, UpdateData &updateData)
{
	GameObject::Update(gameTime, updateData);

	auto viewport = updateData.viewport;

	if (!viewport.Contains(GetBoundingBox()))
		state = ObjectState::DEAD;
}

void Enemy::TakeDamage(int damage)
{
	health -= damage;

	if (health <= 0)
		Die();
}

void Enemy::Die()
{
	SetState(ObjectState::DYING);
	body.Enabled(false);
	Detach<IMovementSystem>();
}
