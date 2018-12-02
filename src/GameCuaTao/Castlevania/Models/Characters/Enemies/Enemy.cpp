#include "Enemy.h"

using namespace Castlevania;

Enemy::Enemy(EntityType type) : GameObject{ type }
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

void Enemy::Update(GameTime gameTime, UpdateData &updateData)
{
	GameObject::Update(gameTime, updateData);

	auto viewport = updateData.viewport;

	if (!viewport.TouchesOrIntersects(GetFrameRect()))
		state = ObjectState::DEAD;
}

void Enemy::TakeDamage(int damage)
{
	health -= damage;

	if (health <= 0)
	{
		SetState(ObjectState::DYING);
		body.Enabled(false);
	}
}