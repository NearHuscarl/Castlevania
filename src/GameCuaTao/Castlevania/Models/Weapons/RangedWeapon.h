#pragma once

#include "../GameObject.h"

namespace Castlevania
{
	// Throwable weapon like Dagger, Axe, Boomerang,...
	class RangedWeapon : public GameObject
	{
	public:
		RangedWeapon(EntityType type);

		void SetOwner(GameObject *owner);
		void Throw();

	private:
		GameObject *owner;
	};
}