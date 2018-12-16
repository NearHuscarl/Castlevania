#pragma once

#include "../GameObject.h"

namespace Castlevania
{
	// Throwable weapon like Dagger, Axe, Boomerang,...
	class RangedWeapon : public GameObject
	{
	public:
		RangedWeapon(ObjectId type);

		void SetOwner(GameObject *owner);
		void Update(GameTime gameTime, UpdateData &updateData);
		void Throw();

	private:
		GameObject *owner;
	};
}