#pragma once

#include "Direct2DGame/GameTime.h"
#include "RectangleObject.h"

namespace Castlevania
{
	class SpawnArea : public RectangleObject
	{
	public:
		SpawnArea(RectF boundingBox);

		void SetActive(bool value);
		void Update(GameTime gameTime);

	private:
		bool isActive;
	};
}