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

		std::unique_ptr<IEffect> CreateSparkEffect();
		std::unique_ptr<IEffect> CreateFlameEffect();
		std::unique_ptr<IEffect> CreateBigFlameEffect();
		std::unique_ptr<IEffect> CreateMoneyTextEffect(int money);
		std::unique_ptr<IEffect> CreateFlashingMoneyTextEffect();
		std::unique_ptr<IEffect> CreateDebrisEffect();
		std::unique_ptr<IEffect> CreateWaterEffect();

	private:
		ContentManager &content;
	};
}