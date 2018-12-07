#pragma once

#include "../Systems/CollisionResponse/ICollisionResponseSystem.h"
#include "../GameObject.h"

namespace Castlevania
{
	class DaggerResponseSystem : public ICollisionResponseSystem
	{
	public:
		DaggerResponseSystem(GameObject &parent);

		virtual void Receive(int message) override {};
		void Update(UpdateData &updateData) override;

	private:
		GameObject &parent;

		void OnCollideWithBrazier(CollisionResult &result, ObjectCollection &objectCollection);
	};
}