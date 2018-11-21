#pragma once

#include "ICollisionResponseSystem.h"

namespace Castlevania
{
	class GameObject;

	// Response to static object only (Clamp move when hitting floor or wall)
	class StaticResponseSystem : public ICollisionResponseSystem
	{
	public:
		StaticResponseSystem(GameObject &parent);

		virtual void Receive(int message) override {};
		virtual void Update(ObjectCollection &objectCollection) override;

	private:
		GameObject &parent;
	};
}