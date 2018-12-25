#include "RangedWeapon.h"
#include "../UpdateData.h"

using namespace Castlevania;

RangedWeapon::RangedWeapon(ObjectId type) : GameObject{ type }
{
	this->throwVelocity = Vector2{ 500, 0 };
}

Vector2 RangedWeapon::GetThrowVelocity()
{
	return throwVelocity;
}

void RangedWeapon::SetThrowVelocity(Vector2 velocity)
{
	throwVelocity = velocity;
}

int RangedWeapon::GetAttack()
{
	return attack;
}

void RangedWeapon::SetAttack(int attack)
{
	this->attack = attack;
}

void RangedWeapon::Update(UpdateData &updateData)
{
	GameObject::Update(updateData);

	auto viewport = updateData.viewport;

	if (!viewport.TouchesOrIntersects(GetFrameRect()))
		Destroy();
}

void RangedWeapon::Throw(Vector2 position)
{
	body.Enabled(true);
	SetVisibility(true);
	SetPosition(position);
	
	velocity = throwVelocity;
	
	if (facing == Facing::Right)
		velocity.x = std::abs(velocity.x);
	else
		velocity.x = -std::abs(velocity.x);
}
