#pragma once

#include "../Systems/CollisionResponse/ResponseSystem.h"

namespace Castlevania
{
	class GameObject;

	class PowerupResponseSystem : public ResponseSystem
	{
	public:
		PowerupResponseSystem(GameObject &parent);
		GameObject &GetParent() override;

	private:
		GameObject &parent;

		void OnTouchingGround(CollisionData collisionData) override;
	};
}