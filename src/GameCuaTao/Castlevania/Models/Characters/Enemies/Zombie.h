#pragma once

#include "Enemy.h"

namespace Castlevania
{
	class Zombie : public Enemy
	{
	public:
		Zombie();

		void WalkRight();
		void WalkLeft();

	private:
		friend class ZombieMovementSystem;
		void StopWalking();
		void Land();
	};
}