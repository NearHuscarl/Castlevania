#include "RangedWeapon.h"
#include "../UpdateData.h"

using namespace Castlevania;

RangedWeapon::RangedWeapon(ObjectId type) : GameObject{ type }
{
	this->owner = nullptr;
	this->throwVelocity = Vector2{ 500, 0 };
}

void RangedWeapon::SetOwner(GameObject *owner)
{
	this->owner = owner;
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

void RangedWeapon::Throw()
{
	if (owner == nullptr)
		return;

	body.Enabled(true);
	SetVisibility(true);
	SetFacing(owner->GetFacing());

	auto playerBbox = owner->GetBoundingBox();
	auto position = Vector2{
		playerBbox.left,
		playerBbox.top + 5
	};
	SetPosition(position);
	
	velocity = throwVelocity;
	
	if (facing == Facing::Right)
		velocity.x = std::abs(velocity.x);
	else
		velocity.x = -std::abs(velocity.x);
}
