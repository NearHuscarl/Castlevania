#include "FishmanResponseSystem.h"
#include "../../UpdateData.h"
#include "../../Areas/WaterArea.h"

using namespace Castlevania;

FishmanResponseSystem::FishmanResponseSystem(Fishman &parent) : parent{ parent }
{
	wasOnGround = false;
}

GameObject &FishmanResponseSystem::GetParent()
{
	return parent;
}

void FishmanResponseSystem::Update(UpdateData &updateData)
{
	auto &objectCollection = *updateData.objectCollection;
	auto collisionData = GetParent().GetBody().GetCollisionData();
	auto isOnGround = false;

	for (auto result : collisionData.collisionResults)
	{
		auto type = (EntityType)result.collidedObject.GetType();

		switch (type)
		{
			case EntityType::Boundary:
			{
				if (result.direction == Direction::Top)
				{
					ClampDistance_Y(collisionData);
					isOnGround = true;
				}
				break;
			}

			case EntityType::WaterArea:
			{
				if (result.direction == Direction::Top)
				{
					auto &waterArea = dynamic_cast<WaterArea&>(result.collidedObject);

					waterArea.Splash(parent.GetOriginPosition());
				}
				break;
			}
		}
	}

	if (wasOnGround != isOnGround)
	{
		if (wasOnGround)
			parent.Freeze();
		else
			parent.Land();

		wasOnGround = isOnGround;
	}
}
