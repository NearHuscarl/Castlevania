#pragma once

#include "Direct2DGame/Base/Vector2.h"
#include "Direct2DGame/Extensions/RectF.h"

namespace Castlevania
{
	struct ObjectCollection;

	enum class SpawnState
	{
		ACTIVE,
		INACTIVE,
		SPAWNING,
	};

	class ISpawner
	{
	public:
		virtual SpawnState GetSpawnState() = 0;
		virtual void Activate() = 0;
		virtual void Deactivate() = 0;
	};
}