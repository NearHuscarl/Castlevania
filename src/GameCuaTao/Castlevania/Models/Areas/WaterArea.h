#pragma once

#include "Direct2DGame/GameTime.h"
#include "../GameObject.h"

namespace Castlevania
{
	class EffectFactory;

	class WaterArea : public GameObject
	{
	public:
		WaterArea(EffectFactory &effectFactory);

		void SpawnWaterEffect(Vector2 position);

	protected:
		EffectFactory &effectFactory;
	};
}