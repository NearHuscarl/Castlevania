#pragma once

#include "../GameObject.h"
#include "../IAttackable.h"

namespace Castlevania
{
	class Fireball : public GameObject, public IAttackable
	{
	public:
		Fireball();

		int GetAttack() override;
		void SetAttack(int attack) override;

		void Update(UpdateData &updateData) override;

	private:
		int attack;
	};
}