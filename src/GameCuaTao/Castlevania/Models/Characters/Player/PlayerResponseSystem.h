#pragma once

#include "../../Systems/CollisionResponse/ICollisionResponseSystem.h"
#include "Player.h"
#include "../../../Models/Factories/ObjectFactory.h"

namespace Castlevania
{
	class PlayerResponseSystem : public ICollisionResponseSystem
	{
	public:
		PlayerResponseSystem(Player &parent, ObjectFactory &objectFactory);

		virtual void Receive(int message) override {};
		void Update(ObjectCollection &objectCollection) override;

	private:
		Player &parent;
		ObjectFactory &objectFactory;

		void ClampDistance_X(CollisionData collisionData);
		void ClampDistance_Y(CollisionData collisionData);
		
		void OnCollideWithBoundary(CollisionResult &result);
		void OnCollideWithHeart(CollisionResult &result);
		void OnCollideWithWhipPowerup(CollisionResult &result);
		void OnCollideWithKnifeItem(CollisionResult &result, ObjectCollection &objectCollection);
	};
}