#pragma once

#include "Enemy.h"

namespace Castlevania
{
	enum class ZombieState
	{
		WALKING,
		HANGING,
	};

	class Zombie : public Enemy
	{
	public:
		Zombie();

		void SetState(ZombieState state);

		void WalkRight();
		void WalkLeft();

	private:
		ZombieState state;
	};
}