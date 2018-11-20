#pragma once

#include "../../Systems/CollisionResponse/ICollisionResponseSystem.h"
#include "Player.h"
#include "../../../Factories/ObjectFactory.h"

namespace Castlevania
{
	class PlayerResponseSystem : public ICollisionResponseSystem
	{
	public:
		PlayerResponseSystem(Player &parent, ObjectFactory &objectFactory);

		void Update(ObjectCollection &objectCollection) override;

	private:
		Player &parent;
		ObjectFactory &objectFactory;

		void ClampDistance_X(CollisionData collisionData);
		void ClampDistance_Y(CollisionData collisionData);
		
		void OnCollideWithBoundary(CollisionResult &result);
		void OnCollideWithHeart(CollisionResult &result);
		void OnCollideWithWhipPowerup(CollisionResult &result);
		void OnCollideWithKnife(CollisionResult &result);
	};
}