#pragma once

#include "ResponseSystem.h"

namespace Castlevania
{
	class GameObject;

	// Response to platform and ground objects (Clamp move when hitting floor, only check for top direction)
	// for generic parent
	class GroundResponseSystem : public ResponseSystem
	{
	public:
		GroundResponseSystem(GameObject &parent);
		GameObject &GetParent() override;

	private:
		GameObject &parent;

		void OnTouchingGround(CollisionData collisionData) override;
	};
}