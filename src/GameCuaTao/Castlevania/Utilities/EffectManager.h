#pragma once

#include <vector>
#include "Direct2DGame/Extensions/Sprites/Sprite.h"

namespace Castlevania
{
	class EffectManager
	{
	public:
		void SpawnFlameEffect();
		void SpawnMoneyText(int value);

	private:
		std::vector<Sprite> effects;
	};
}