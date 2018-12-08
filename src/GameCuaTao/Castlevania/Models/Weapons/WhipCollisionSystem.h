#pragma once

#include "Direct2DGame/Extensions/Collisions/Body/CollisionData.h"
#include "../Systems/Collision/ICollisionSystem.h"
#include "../GameObject.h"

namespace Castlevania
{
	// Most of the enemies in game have very thin bounding boxes at the
	//	middle of the sprite's width, it helps make enemy movement and player
	//	collision repsonse look more like the original game. But at the same
	//	time make player's weapon harder to register a hit because the bbox is
	//	too small. So the easy way to fix is just use the sprite rectangles
	//	which is a rectangle cover the enemy texture to draw animation, a little
	//	less precise to detect collision but works okay in this case
	class WhipCollisionSystem : public ICollisionSystem
	{
	public:
		WhipCollisionSystem(GameObject &parent);

		void Receive(int message) override {};
		void Update(ObjectCollection &objectCollection) override;

	protected:
		GameObject &parent;
	};
}