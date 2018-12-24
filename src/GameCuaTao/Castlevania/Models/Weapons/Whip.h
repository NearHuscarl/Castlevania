#pragma once

#include <map>
#include "../GameObject.h"
#include "../IAttackable.h"

namespace Castlevania
{
	constexpr auto WHIP_MAX_LEVEL = 3;

	class Whip : public GameObject, public IAttackable
	{
	public:
		Whip(GameObject &owner);

		int GetLevel();
		void SetLevel(int level);
		int GetAttack() override;
		void SetAttack(int attack) override;
		GameObject &GetOwner();
		void SetFacing(Facing facing) override;

		void LoadContent(ContentManager &content) override;

		void Unleash();
		void Withdraw();
		void Upgrade();

	private:
		GameObject &owner;
		int level; // lvl 1-3
	};
}