#pragma once

#include "../GameObject.h"

namespace Castlevania
{
	enum class RangedWeaponState
	{
		Sheathed,
		Flying,
	};

	// Throwable weapon like Dagger, Axe, Boomerang,...
	class RangedWeapon : public GameObject
	{
	public:
		RangedWeapon(EntityType type);

		RangedWeaponState GetState();
		void SetOwner(GameObject *owner);
		void Throw();

		void Draw(SpriteExtensions &spriteBatch);

	private:
		GameObject *owner;
		RangedWeaponState state;
	};
}