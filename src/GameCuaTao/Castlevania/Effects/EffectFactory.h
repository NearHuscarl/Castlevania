#pragma once

#include <vector>
#include "Direct2DGame/Content/ContentManager.h"
#include "IEffect.h"

namespace Castlevania
{
	class EffectFactory
	{
	public:
		EffectFactory(ContentManager &content);

		std::unique_ptr<IEffect> CreateFlameEffect();
		//void SpawnMoneyText(Vector2 position, int value);

	private:
		ContentManager &content;
	};
}