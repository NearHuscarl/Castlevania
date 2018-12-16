#pragma once

#include "../../Systems/CollisionResponse/ResponseSystem.h"
#include "Panther.h"

namespace Castlevania
{
	class PantherResponseSystem : public ResponseSystem
	{
	public:
		PantherResponseSystem(Panther &parent);
		GameObject &GetParent() override;

	private:
		Panther &parent;

		void OnTouchingGround(CollisionData collisionData) override;
		void OnFalling() override;
		void OnLanding() override;
	};
}