#pragma once

#include <map>
#include "../GameObject.h"

namespace Castlevania
{
	class Whip : public GameObject
	{
	public:
		Whip(GameObject &owner);

		void SetFacing(Facing facing);

		void LoadContent(ContentManager &content) override;
		void Draw(SpriteExtensions &spriteBatch) override;

		void Unleash();
		void Withdraw();

	private:
		Facing facing;
		Vector2 GetPositionRelativeToPlayer(GameObject &player);
		GameObject &owner;
		int level; // 1, 2, 3
		int hitPoint;
		bool isActive;
	};
}