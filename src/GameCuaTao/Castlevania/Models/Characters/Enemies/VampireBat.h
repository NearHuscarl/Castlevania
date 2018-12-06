#pragma once

#include "Enemy.h"

namespace Castlevania
{
	class VampireBat : public Enemy
	{
	public:
		VampireBat();

		bool IsActive();
		void SetActive(bool value);

		void FlyRight();
		void FlyLeft();

	private:
		bool isActive;
	};
}