#pragma once

#include "../../GameObject.h"

namespace Castlevania
{
	class Enemy : public GameObject
	{
	public:
		Enemy(EntityType type);

		void SetHealth(int health);
		int GetAttack();
		void SetAttack(int attack);
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