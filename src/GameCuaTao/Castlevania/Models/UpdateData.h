#pragma once

#include "Characters/Player/Player.h"
#include "Factories/ObjectCollection.h"

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