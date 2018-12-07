#pragma once

#include "ICollisionResponseSystem.h"
#include "Direct2DGame/Extensions/Collisions/Body/CollisionData.h"

namespace Castlevania
{
	class GameObject;

	// Base class to handle collision to platform and ground/floor objects
	class ResponseSystem : public ICollisionResponseSystem
	{
	public:
		ResponseSystem();

		virtual GameObject &GetParent();
		virtual void Receive(int message) override {};
		virtual void Update(UpdateData &updateData) override;

	protected:
		virtual void OnTouchingGround(CollisionData collisionData);
		virtual void OnFalling();
		virtual void OnLanding();

		void ClampDistance_X(CollisionData collisionData);
		void ClampDistance_Y(CollisionData collisionData);

	private:
		bool wasOnGround;
	};
}