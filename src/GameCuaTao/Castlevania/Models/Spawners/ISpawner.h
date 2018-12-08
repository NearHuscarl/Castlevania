#pragma once

#include "Direct2DGame/Base/Vector2.h"
#include "Direct2DGame/Extensions/RectF.h"

namespace Castlevania
{
	struct ObjectCollection;

	class ISpawner
	{
	public:
		virtual void Activate() = 0;
		virtual void Deactivate() = 0;

	private:
		virtual void SpawnObject(ObjectCollection &objectCollection, RectF viewport) = 0;
	};
}