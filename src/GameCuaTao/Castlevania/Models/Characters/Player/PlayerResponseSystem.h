#pragma once

#include "../../Systems/CollisionResponse/ResponseSystem.h"
#include "../../../Models/Factories/ObjectFactory.h"
#include "Player.h"

namespace Castlevania
{
	class PlayerResponseSystem : public ResponseSystem
	{
	public:
		PlayerResponseSystem(Player &parent, ObjectFactory &objectFactory);

		GameObject &GetParent() override;
		void Update(UpdateData &updateData) override;

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
		Direction GetPlayerHitDirection(GameObject &object, Direction direction);

		void OnFalling() override;

		void OnCollideWithBoundary(CollisionResult &result, ResponseResult &responseResult);
		void OnCollideWithTrigger(CollisionResult &result, ResponseResult &responseResult);
		void OnCollideWithEnemy(CollisionResult &result);
		void OnCollideWithFireball(CollisionResult &result);
		void OnCollideWithHeart(CollisionResult &result);
		void OnCollideWithWhipPowerup(CollisionResult &result);
		void OnCollideWithDaggerItem(CollisionResult &result, ObjectCollection &objectCollection);

		void OnCollideWithStairUpTrigger(Trigger &trigger, ResponseResult &responseResult);
		void OnCollideWithStairDownTrigger(Trigger &trigger, ResponseResult &responseResult);
		void OnCollideWithNextMapTrigger(Trigger &trigger);
		void OnCollideWithCastleEntranceTrigger(Trigger &trigger);
	};
}