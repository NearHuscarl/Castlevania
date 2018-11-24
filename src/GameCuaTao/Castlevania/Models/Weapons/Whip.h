#pragma once

#include <map>
#include "../GameObject.h"

namespace Castlevania
{
	constexpr auto WHIP_MAX_LEVEL = 3;

	class Whip : public GameObject
	{
	public:
		Whip(GameObject &owner);

		int GetLevel();
		GameObject &GetOwner();
		void SetFacing(Facing facing) override;

		void LoadContent(ContentManager &content) override;

		void Unleash();
		void Withdraw();
		void Upgrade();

	private:
		GameObject &owner;
		int level; // 1, 2, 3
		int hitPoint;
	};
}