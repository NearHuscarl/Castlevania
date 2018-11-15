#pragma once

#include "Body/IColliable.h"

namespace Castlevania
{
	class RectangleObject : public IColliable
	{
	public:
		RectangleObject(Rect rect);

		EntityType GetType() override;
		Vector2 GetPosition() override;
		Rect GetBoundingBox() override;

	private:
		EntityType type;
		Vector2 position;
		Rect boundingBox;
	};
}