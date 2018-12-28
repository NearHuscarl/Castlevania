#pragma once

#include "../../GameObject.h"
#include "../../IAttackable.h"
#include "../../Health.h"

namespace Castlevania
{
	class Enemy : public GameObject, public IAttackable
	{
	public:
		Enemy(ObjectId type);

		Health &GetHealthRef();
		void SetHealth(int value);
		int GetAttack() override;
		void SetAttack(int value) override;
		void SetExp(int value);
		int GetExp();

		virtual void Update(UpdateData &updateData) override;
		void TakeDamage(int damage);
		void Die();

	private:
		Health health;
		int attack;
		int exp;
	};
}