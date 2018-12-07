#pragma once

#include "../../GameObject.h"
#include "../../IAttackable.h"

namespace Castlevania
{
	class Enemy : public GameObject, public IAttackable
	{
	public:
		Enemy(EntityType type);

		void SetHealth(int health);
		int GetAttack() override;
		void SetAttack(int attack) override;
		void SetExp(int exp);
		int GetExp();

		virtual void Update(GameTime gameTime, UpdateData &updateData) override;
		void TakeDamage(int damage);

	private:
		int health;
		int attack;
		int exp;
	};
}