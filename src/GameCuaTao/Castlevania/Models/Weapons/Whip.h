#pragma once

#include <map>
#include "../AnimatedObject.h"

namespace Castlevania
{
	constexpr auto WHIP_MAX_LEVEL = 3;

	class Whip : public AnimatedObject
	{
	public:
		Whip(GameObject &owner);

		void SetFacing(Facing facing);
		RectF GetBoundingBox() override;
		int GetLevel();

		void LoadContent(ContentManager &content) override;
		void Update(float deltaTime, ObjectCollection *objectCollection) override;
		void Draw(SpriteExtensions &spriteBatch) override;

		void Unleash();
		void Withdraw();
		void Upgrade();

	private:
		Vector2 GetPositionRelativeToPlayer(GameObject &player);
		GameObject &owner;
		int level; // 1, 2, 3
		int hitPoint;
	};
}