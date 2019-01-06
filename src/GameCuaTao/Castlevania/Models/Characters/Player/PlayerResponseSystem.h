#pragma once

#include "../../Systems/CollisionResponse/ResponseSystem.h"
#include "../../../Models/Factories/ObjectFactory.h"
#include "Player.h"

namespace Castlevania
{
	struct ObjectCollection;

	class PlayerResponseSystem : public ResponseSystem
	{
	public:
		PlayerResponseSystem(Player &parent, ObjectFactory &objectFactory);

		GameObject &GetParent() override;
		void Update(UpdateData &updateData) override;

	private:
		struct ResponseResult;

		Player &parent;
		ObjectFactory &objectFactory;
		bool wasOnGround;

		void PostProcess(ResponseResult responseResult);
		Direction GetPlayerHitDirection(GameObject &object, Direction direction);

		void OnFalling() override;

		void OnCollideWithBoundary(CollisionResult &result, ResponseResult &responseResult);
		void OnCollideWithTrigger(CollisionResult &result, ResponseResult &responseResult);
		void OnCollideWithBossFightArea(CollisionResult &result, Rect viewport);
		void OnCollideWithWaterArea(CollisionResult &result, ObjectCollection &objectCollection);
		void OnCollideWithEnemy(CollisionResult &result);
		void OnCollideWithVampireBat(CollisionResult &result);
		void OnCollideWithFireball(CollisionResult &result);
		void OnCollideWithMoneyBag(CollisionResult &result);
		void OnCollideWithSubWeaponItem(CollisionResult &result);
		void OnCollideWithCross(CollisionResult &result);
		void OnCollideWithHeart(CollisionResult &result);
		void OnCollideWithSmallHeart(CollisionResult &result);
		void OnCollideWithInvisibleJar(CollisionResult &result);
		void OnCollideWithPorkChop(CollisionResult &result);
		void OnCollideWithWhipPowerup(CollisionResult &result);
		void OnCollideWithDoubleShot(CollisionResult &result);
		void OnCollideWithCrystalBall(CollisionResult &result);
		void OnCollideWithDoor(CollisionResult &result, ResponseResult &responseResult);

		void OnCollideWithStairUpTrigger(Trigger &trigger);
		void OnCollideWithStairDownTrigger(Trigger &trigger);
		void OnCollideWithNextMapTrigger(Trigger &trigger);
		void OnCollideWithMoneyBagTrigger(Trigger &trigger);
		void OnCollideWithCastleEntranceTrigger(Trigger &trigger);
	};
}