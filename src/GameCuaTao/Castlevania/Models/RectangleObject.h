#pragma once

#include "GameObject.h"

namespace Castlevania
{
	class RectangleObject : public GameObject
	{
	public:
		RectangleObject(RectF boundingBox);

		RectF GetBoundingBox() override;

		~RectangleObject();

	protected:
		RectF boundingBox;
	};
}