#pragma once

#include "../GameObject.h"

namespace Castlevania
{
	// Throwable weapon like Knife, Axe, Boomerang,...
	class RangedWeapon : public GameObject
	{
	public:
		RangedWeapon(EntityType type);

		void SetOwner(GameObject *owner);
		void Throw();

		void Draw(SpriteExtensions &spriteBatch);

	private:
		GameObject *owner;
	};
}