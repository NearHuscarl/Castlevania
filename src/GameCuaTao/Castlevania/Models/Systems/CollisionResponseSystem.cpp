#include "CollisionResponseSystem.h"
#include "../GameObject.h"

using namespace Castlevania;

CollisionResponseSystem::CollisionResponseSystem(GameObject &parent) : parent{ parent }
{
}

void CollisionResponseSystem::Update(CollisionData collisionData)
{
	auto distance = parent.GetDistance();

	if (collisionData.collisionResults.size() == 0)
	{
		parent.Move(distance);
		return;
	}

	auto normal = collisionData.minNormal;
	auto time = collisionData.minTime;

	// *0.4f : need to push out a bit to avoid overlapping next frame
	distance = distance * time + normal * 0.4f;

	auto velocity = parent.GetVelocity();

	if (normal.x != 0)
		velocity.x = 0;
	if (normal.y != 0)
		velocity.y = 0;

	parent.Move(distance);
	parent.SetVelocity(velocity);
}
