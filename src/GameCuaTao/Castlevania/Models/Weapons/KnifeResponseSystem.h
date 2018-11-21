#pragma once

#include "../Systems/CollisionResponse/ICollisionResponseSystem.h"
#include "../GameObject.h"

namespace Castlevania
{
	class KnifeResponseSystem : public ICollisionResponseSystem
	{
	public:
		KnifeResponseSystem(GameObject &parent);

		virtual void Receive(int message) override {};
		void Update(ObjectCollection &objectCollection);

	private:
		GameObject &parent;

		void OnCollideWithBoundary(CollisionResult &result);
	};
}