#include "WaterAreaResponseSystem.h"

using namespace Castlevania;

WaterAreaResponseSystem::WaterAreaResponseSystem(WaterArea &parent, EffectFactory &effectFactory) :
	parent{ parent },
	effectFactory{ effectFactory }
{
}

void WaterAreaResponseSystem::Update(UpdateData &updateData)
{
	//auto collisionData = parent.GetBody().GetCollisionData();
	//auto collideWithPlayer = false;

	//for (auto result : collisionData.collisionResults)
	//{
	//	auto type = (EntityType)result.collidedObject.GetType();

	//	switch (type)
	//	{
	//		case EntityType::Player:
	//			collideWithPlayer = true;
	//			break;
	//	}
	//}

	//switch (parent.GetSpawnState())
	//{
	//	case SpawnState::ACTIVE:
	//		if (!collideWithPlayer)
	//			parent.Deactivate();
	//		break;

	//	case SpawnState::INACTIVE:
	//		if (collideWithPlayer)
	//			parent.Activate();
	//		break;
	//}
}
