#pragma once

#include "ICollisionResponseSystem.h"

namespace Castlevania
{
	class GameObject;

	// Response to platform and ground objects (Clamp move when hitting floor, only check for top direction)
	class GroundResponseSystem : public ICollisionResponseSystem
	{
	public:
		GroundResponseSystem(GameObject &parent);

		virtual void Receive(int message) override {};
		virtual void Update(ObjectCollection &objectCollection) override;

	private:
		GameObject &parent;
		bool wasOnGround;
	};
}