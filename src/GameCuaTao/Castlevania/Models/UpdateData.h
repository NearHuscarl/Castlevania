#pragma once

#include "Characters/Player/Player.h"
#include "../Scenes/Stages/StageObject.h"
#include "../Utilities/CollisionObject.h"

namespace Castlevania
{
	struct UpdateData
	{
		GameTime gameTime;
		RectF viewport;
		Player *player;
		bool isStopwatchActive;
		ObjectCollection *objects;
		std::vector<GameObject*> *collisionObjects;
	};
}