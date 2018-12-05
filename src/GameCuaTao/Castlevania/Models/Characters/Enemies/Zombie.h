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
		void StopWalking();
		void Land();

		friend class ZombieResponseSystem;
	};
}