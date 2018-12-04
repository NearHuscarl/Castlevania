#pragma once

#include "../../Systems/CollisionResponse/ICollisionResponseSystem.h"
#include "../../../Models/Factories/ObjectFactory.h"
#include "Player.h"

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
		bool wasOnGround;

		struct ResponseResult
		{
			bool isOnGround;
			Trigger *stairTrigger;
		};

		void PostProcess(ResponseResult responseResult);

		void ClampDistance_X(CollisionData collisionData);
		void ClampDistance_Y(CollisionData collisionData);
		
		void OnCollideWithBoundary(CollisionResult &result, ResponseResult &responseResult);
		void OnCollideWithTrigger(CollisionResult &result, ResponseResult &responseResult);
		void OnCollideWithEnemy(CollisionResult &result);
		void OnCollideWithHeart(CollisionResult &result);
		void OnCollideWithWhipPowerup(CollisionResult &result);
		void OnCollideWithDaggerItem(CollisionResult &result, ObjectCollection &objectCollection);

		void OnCollideWithStairUpTrigger(Trigger &trigger, ResponseResult &responseResult);
		void OnCollideWithStairDownTrigger(Trigger &trigger, ResponseResult &responseResult);
		void OnCollideWithNextMapTrigger(Trigger &trigger);
		void OnCollideWithCastleEntranceTrigger(Trigger &trigger);
	};
}