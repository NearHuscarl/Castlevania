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
