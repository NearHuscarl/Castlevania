#pragma once

#include "../Systems/CollisionResponse/ICollisionResponseSystem.h"
#include "Whip.h"

namespace Castlevania
{
	class WhipResponseSystem : public ICollisionResponseSystem
	{
	public:
		WhipResponseSystem(Whip &parent);

		virtual void Receive(int message) override {};
		void Update(ObjectCollection &objectCollection);

	private:
		Whip &parent;

		void OnCollideWithFirePit(CollisionResult &result, ObjectCollection &objectCollection);
	};
}