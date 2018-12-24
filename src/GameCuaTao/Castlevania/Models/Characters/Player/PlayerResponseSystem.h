#pragma once

#include "../../Systems/CollisionResponse/ResponseSystem.h"
#include "../../../Models/Factories/ObjectFactory.h"
#include "../../../Scenes/Stages/StageObject.h"
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
		void OnCollideWithWaterArea(CollisionResult &result, StageObject &stageObject);
		void OnCollideWithEnemy(CollisionResult &result);
		void OnCollideWithVampireBat(CollisionResult &result);
		void OnCollideWithFireball(CollisionResult &result);
		void OnCollideWithMoneyBag(CollisionResult &result);
		void OnCollideWithHeart(CollisionResult &result);
		void OnCollideWithSmallHeart(CollisionResult &result);
		void OnCollideWithWhipPowerup(CollisionResult &result);
		void OnCollideWithSubWeaponItem(CollisionResult &result);
		void OnCollideWithDoor(CollisionResult &result, ResponseResult &responseResult);

		void OnCollideWithStairUpTrigger(Trigger &trigger);
		void OnCollideWithStairDownTrigger(Trigger &trigger);
		void OnCollideWithNextMapTrigger(Trigger &trigger);
		void OnCollideWithCastleEntranceTrigger(Trigger &trigger);
	};
}